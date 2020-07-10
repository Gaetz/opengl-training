#pragma once
#include "MoveComponent.h"
#include <SDL_stdinc.h>

class InputComponent : public MoveComponent
{
public:
	InputComponent(Actor& ownerP);

	void processInput(const Uint8* keyState);

	void setMaxForwardSpeed(float maxForwardSpeedP);
	void setMaxAngularSpeed(float maxAngularSpeedP);
	void setForwardKey(int key);
	void setBackKey(int key);
	void setClockwiseKey(int key);
	void setCounterClockwiseKey(int key);


private:
	float maxForwardSpeed;
	float maxAngularSpeed;

	int forwardKey;
	int backKey;
	int clockwiseKey;
	int counterClockwiseKey;
};

