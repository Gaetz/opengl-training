// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Matrix4.h"
#include <string>

class SoundEvent
{
public:
	SoundEvent();
	// Returns true if associated FMOD event still exists
	bool isValid();
	// Restart event from begining
	void restart();
	// Stop this event
	void stop(bool allowFadeOut = true);
	// Setters
	void setPaused(bool pause);
	void setVolume(float value);
	void setPitch(float value);
	void setParameter(const std::string& name, float value);
	// Getters
	bool getPaused() const;
	float getVolume() const;
	float getPitch() const;
	float getParameter(const std::string& name);
	// Positional
	bool is3D() const;
	void set3DAttributes(const Matrix4& worldTrans);
protected:
	// Make this constructor protected and AudioSystem a friend
	// so that only AudioSystem can access this constructor.
	friend class AudioSystem;
	SoundEvent(class AudioSystem* system, unsigned int id);
private:
	class AudioSystem* system;
	unsigned int id;
};