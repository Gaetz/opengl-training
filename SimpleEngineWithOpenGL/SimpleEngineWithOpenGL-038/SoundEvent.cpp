// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SoundEvent.h"
#include "AudioSystem.h"
#include <fmod_studio.hpp>

SoundEvent::SoundEvent(class AudioSystem* systemP, unsigned int id):
	system(systemP),
	id(id)
{
}

SoundEvent::SoundEvent(): 
	system(nullptr),
	id(0)
{
}

bool SoundEvent::isValid()
{
	return (system && system->getEventInstance(id) != nullptr);
}

void SoundEvent::restart()
{
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->start();
	}
}

void SoundEvent::stop(bool allowFadeOut /* true */)
{
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		FMOD_STUDIO_STOP_MODE mode = allowFadeOut ?
			FMOD_STUDIO_STOP_ALLOWFADEOUT :
			FMOD_STUDIO_STOP_IMMEDIATE;
		event->stop(mode);
	}
}

void SoundEvent::setPaused(bool pause)
{
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->setPaused(pause);
	}
}

void SoundEvent::setVolume(float value)
{
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->setVolume(value);
	}
}

void SoundEvent::setPitch(float value)
{
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->setPitch(value);
	}
}

void SoundEvent::setParameter(const std::string& name, float value)
{
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->setParameterValue(name.c_str(), value);
	}
}

bool SoundEvent::getPaused() const
{
	bool retVal = false;
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->getPaused(&retVal);
	}
	return retVal;
}

float SoundEvent::getVolume() const
{
	float retVal = 0.0f;
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->getVolume(&retVal);
	}
	return retVal;
}

float SoundEvent::getPitch() const
{
	float retVal = 0.0f;
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->getPitch(&retVal);
	}
	return retVal;
}

float SoundEvent::getParameter(const std::string& name)
{
	float retVal = 0.0f;
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		event->getParameterValue(name.c_str(), &retVal);
	}
	return retVal;
}

bool SoundEvent::is3D() const
{
	bool retVal = false;
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		// Get the event description
		FMOD::Studio::EventDescription* ed = nullptr;
		event->getDescription(&ed);
		if (ed)
		{
			ed->is3D(&retVal);
		}
	}
	return retVal;
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

void SoundEvent::set3DAttributes(const Matrix4& worldTrans)
{
	auto event = system ? system->getEventInstance(id) : nullptr;
	if (event)
	{
		FMOD_3D_ATTRIBUTES attr;
		// Set position, forward, up
		attr.position = VecToFMOD(worldTrans.getTranslation());
		// In world transform, first row is forward
		attr.forward = VecToFMOD(worldTrans.getXAxis());
		// Third row is up
		attr.up = VecToFMOD(worldTrans.getZAxis());
		// Set velocity to zero (fix if using Doppler effect)
		attr.velocity = { 0.0f, 0.0f, 0.0f };
		event->set3DAttributes(&attr);
	}
}
