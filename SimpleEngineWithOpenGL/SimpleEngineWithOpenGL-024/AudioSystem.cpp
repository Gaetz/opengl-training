// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AudioSystem.h"
#include "Log.h"
#include "Game.h"

#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <SDL_Log.h>
#include <sstream>

unsigned int AudioSystem::nextID = 0;

AudioSystem::AudioSystem(): system(nullptr), lowLevelSystem(nullptr)
{
}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::initialize()
{
	// Initialize debug logging
	FMOD::Debug_Initialize(
		FMOD_DEBUG_LEVEL_ERROR, // Log only errors
		FMOD_DEBUG_MODE_TTY // Output to stdout
	);

	// Create FMOD studio system object
	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&system);
	if (result != FMOD_OK)
	{
		std::ostringstream error;
		error << "Failed to create FMOD system: " << FMOD_ErrorString(result);
		Log::error(LogCategory::Audio, error.str());
		return false;
	}

	// Initialize FMOD studio system
	result = system->initialize(
		512, // Max number of concurrent sounds
		FMOD_STUDIO_INIT_NORMAL, // Use default settings
		FMOD_INIT_NORMAL, // Use default settings
		nullptr // Usually null
	);
	if (result != FMOD_OK)
	{
		std::ostringstream error;
		error << "Failed to initialize FMOD system: " << FMOD_ErrorString(result);
		Log::error(LogCategory::Audio, error.str());
		return false;
	}

	// Save the low-level system pointer
	system->getLowLevelSystem(&lowLevelSystem);

	// Load the master banks (strings first)
	loadBank("Res/Audio/Master Bank.strings.bank");
	loadBank("Res/Audio/Master Bank.bank");

	return true;
}

void AudioSystem::close()
{
	// Unload all banks
	unloadAllBanks();
	// Shutdown FMOD system
	if (system)
	{
		system->release();
	}
}

void AudioSystem::loadBank(const std::string& name)
{
	// Prevent double-loading
	if (banks.find(name) != banks.end())
	{
		return;
	}

	// Try to load bank
	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = system->loadBankFile(
		name.c_str(), // File name of bank
		FMOD_STUDIO_LOAD_BANK_NORMAL, // Normal loading
		&bank // Save pointer to bank
	);

	const int maxPathLength = 512;
	if (result == FMOD_OK)
	{
		// Add bank to map
		banks.emplace(name, bank);
		// Load all non-streaming sample data
		bank->loadSampleData();
		// Get the number of events in this bank
		int numEvents = 0;
		bank->getEventCount(&numEvents);
		if (numEvents > 0)
		{
			// Get list of event descriptions in this bank
			std::vector<FMOD::Studio::EventDescription*> eventDescriptions(numEvents);
			bank->getEventList(eventDescriptions.data(), numEvents, &numEvents);
			char eventName[maxPathLength];
			for (int i = 0; i < numEvents; i++)
			{
				FMOD::Studio::EventDescription* e = eventDescriptions[i];
				// Get the path of this event (like event:/Explosion2D)
				e->getPath(eventName, maxPathLength, nullptr);
				// Add to event map
				events.emplace(eventName, e);
			}
		}
		// Get the number of buses in this bank
		int numBuses = 0;
		bank->getBusCount(&numBuses);
		if (numBuses > 0)
		{
			// Get list of buses in this bank
			std::vector<FMOD::Studio::Bus*> bankBuses(numBuses);
			bank->getBusList(bankBuses.data(), numBuses, &numBuses);
			char busName[512];
			for (int i = 0; i < numBuses; i++)
			{
				FMOD::Studio::Bus* bus = bankBuses[i];
				// Get the path of this bus (like bus:/SFX)
				bus->getPath(busName, 512, nullptr);
				// Add to buses map
				buses.emplace(busName, bus);
			}
		}
	}
}

void AudioSystem::unloadBank(const std::string& name)
{
	// Ignore if not loaded
	auto iter = banks.find(name);
	if (iter == banks.end())
	{
		return;
	}

	// First we need to remove all events from this bank
	FMOD::Studio::Bank* bank = iter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0)
	{
		// Get event descriptions for this bank
		std::vector<FMOD::Studio::EventDescription*> eventDescriptions(numEvents);
		// Get list of events
		bank->getEventList(eventDescriptions.data(), numEvents, &numEvents);
		char eventName[512];
		for (int i = 0; i < numEvents; i++)
		{
			FMOD::Studio::EventDescription* e = eventDescriptions[i];
			// Get the path of this event
			e->getPath(eventName, 512, nullptr);
			// Remove this event
			auto eventi = events.find(eventName);
			if (eventi != events.end())
			{
				events.erase(eventi);
			}
		}
	}
	// Get the number of buses in this bank
	int numBuses = 0;
	bank->getBusCount(&numBuses);
	if (numBuses > 0)
	{
		// Get list of buses in this bank
		std::vector<FMOD::Studio::Bus*> bankBuses(numBuses);
		bank->getBusList(bankBuses.data(), numBuses, &numBuses);
		char busName[512];
		for (int i = 0; i < numBuses; i++)
		{
			FMOD::Studio::Bus* bus = bankBuses[i];
			// Get the path of this bus (like bus:/SFX)
			bus->getPath(busName, 512, nullptr);
			// Remove this bus
			auto busi = buses.find(busName);
			if (busi != buses.end())
			{
				buses.erase(busi);
			}
		}
	}

	// Unload sample data and bank
	bank->unloadSampleData();
	bank->unload();
	// Remove from banks map
	banks.erase(iter);
}

void AudioSystem::unloadAllBanks()
{
	for (auto& iter : banks)
	{
		// Unload the sample data, then the bank itself
		iter.second->unloadSampleData();
		iter.second->unload();
	}
	banks.clear();
	// No banks means no events
	events.clear();
}

SoundEvent AudioSystem::playEvent(const std::string& name)
{
	unsigned int retID = 0;
	auto iter = events.find(name);
	if (iter != events.end())
	{
		// Create instance of event
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event)
		{
			// Start the event instance
			event->start();
			// Get the next id, and add to map
			nextID++;
			retID = nextID;
			eventInstances.emplace(retID, event);
		}
	}
	return SoundEvent(this, retID);
}

void AudioSystem::update(float dt)
{
	// Find any stopped event instances
	std::vector<unsigned int> done;
	for (auto& iter : eventInstances)
	{
		FMOD::Studio::EventInstance* e = iter.second;
		// Get the state of this event
		FMOD_STUDIO_PLAYBACK_STATE state;
		e->getPlaybackState(&state);
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			// Release the event and add id to done
			e->release();
			done.emplace_back(iter.first);
		}
	}

	// Remove done event instances from map
	for (auto id : done)
	{
		eventInstances.erase(id);
	}

	// Update FMOD
	system->update();
}

namespace
{
	FMOD_VECTOR VecToFMOD(const Vector3& in)
	{
		// Convert from our coordinates (+x forward, +y right, +z up)
		// to FMOD (+z forward, +x right, +y up)
		FMOD_VECTOR v;
		v.x = in.y;
		v.y = in.z;
		v.z = in.x;
		return v;
	}
}

void AudioSystem::setListener(const Matrix4& viewMatrix)
{
	// Invert the view matrix to get the correct vectors
	Matrix4 invView = viewMatrix;
	invView.invert();
	FMOD_3D_ATTRIBUTES listener;
	// Set position, forward, up
	listener.position = VecToFMOD(invView.getTranslation());
	// In the inverted view, third row is forward
	listener.forward = VecToFMOD(invView.getZAxis());
	// In the inverted view, second row is up
	listener.up = VecToFMOD(invView.getYAxis());
	// Set velocity to zero (fix if using Doppler effect)
	listener.velocity = { 0.0f, 0.0f, 0.0f };
	// Send to FMOD
	system->setListenerAttributes(0, &listener);
}

float AudioSystem::getBusVolume(const std::string& name) const
{
	float retVal = 0.0f;
	const auto iter = buses.find(name);
	if (iter != buses.end())
	{
		iter->second->getVolume(&retVal);
	}
	return retVal;
}

bool AudioSystem::getBusPaused(const std::string& name) const
{
	bool retVal = false;
	const auto iter = buses.find(name);
	if (iter != buses.end())
	{
		iter->second->getPaused(&retVal);
	}
	return retVal;
}

void AudioSystem::setBusVolume(const std::string& name, float volume)
{
	auto iter = buses.find(name);
	if (iter != buses.end())
	{
		iter->second->setVolume(volume);
	}
}

void AudioSystem::setBusPaused(const std::string& name, bool pause)
{
	auto iter = buses.find(name);
	if (iter != buses.end())
	{
		iter->second->setPaused(pause);
	}
}

FMOD::Studio::EventInstance* AudioSystem::getEventInstance(unsigned int id)
{
	FMOD::Studio::EventInstance* event = nullptr;
	auto iter = eventInstances.find(id);
	if (iter != eventInstances.end())
	{
		event = iter->second;
	}
	return event;
}
