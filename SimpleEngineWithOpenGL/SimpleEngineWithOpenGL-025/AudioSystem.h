// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <unordered_map>
#include <string>

#include "SoundEvent.h"
#include "Matrix4.h"

// Forward declarations to avoid including FMOD header
namespace FMOD
{
	class System;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};
};

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	bool initialize();
	void close();

	// Load/unload banks
	void loadBank(const std::string& name);
	void unloadBank(const std::string& name);
	void unloadAllBanks();

	SoundEvent playEvent(const std::string& name);

	void update(float dt);

	// For positional audio
	void setListener(const Matrix4& viewMatrix);
	// Control buses
	float getBusVolume(const std::string& name) const;
	bool getBusPaused(const std::string& name) const;
	void setBusVolume(const std::string& name, float volume);
	void setBusPaused(const std::string& name, bool pause);
protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* getEventInstance(unsigned int id);
private:
	// Tracks the next ID to use for event instances
	static unsigned int nextID;

	// Map of loaded banks
	std::unordered_map<std::string, FMOD::Studio::Bank*> banks;
	// Map of event name to EventDescription
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> events;
	// Map of event id to EventInstance
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> eventInstances;
	// Map of buses
	std::unordered_map<std::string, FMOD::Studio::Bus*> buses;
	// FMOD studio system
	FMOD::Studio::System* system;
	// FMOD Low-level system (in case needed)
	FMOD::System* lowLevelSystem;
};