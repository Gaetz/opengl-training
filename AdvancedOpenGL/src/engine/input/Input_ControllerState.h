#ifndef INPUT_CONTROLLER_STATE_H
#define INPUT_CONTROLLER_STATE_H

#include "Input_KeyStatus.h"
#include "../maths/Vector2.h"

#ifdef __linux__
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_gamecontroller.h>
#elif _WIN32
#include <SDL_stdinc.h>
#include <SDL_gamecontroller.h>
#endif

class ControllerState
{
public:
	friend class InputManager;

	ControllerState();

	bool getButtonValue(SDL_GameControllerButton button) const;
	enum class KeyStatus getButtonState(SDL_GameControllerButton button) const;

	const Vector2& getLeftStick() const { return leftStick; }
	const Vector2& getRightStick() const { return rightStick; }
	float getLeftTrigger() const { return leftTrigger; }
	float getRightTrigger() const { return rightTrigger; }
	bool getIsConnected() const { return isConnected; }


private:
	Uint8 currentButtons[SDL_CONTROLLER_BUTTON_MAX];
	Uint8 previousButtons[SDL_CONTROLLER_BUTTON_MAX];
	Vector2 leftStick;
	Vector2 rightStick;
	float leftTrigger;
	float rightTrigger;
	bool isConnected;
};

#endif