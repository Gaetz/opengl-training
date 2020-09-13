#include "Input_ControllerState.h"
#include "InputManager.h"


ControllerState::ControllerState() :
	leftStick(Vector2()),
	rightStick(Vector2()),
	leftTrigger(0.0f),
	rightTrigger(0.0f),
	isConnected(false)
{

}

bool ControllerState::getButtonValue(SDL_GameControllerButton button) const
{
    return currentButtons[button] == 1;
}

KeyStatus ControllerState::getButtonState(SDL_GameControllerButton button) const
{
	if (previousButtons[button] == 0)
	{
		if (currentButtons[button] == 0)
		{
			return KeyStatus::None;
		}
		else
		{
			return KeyStatus::JustPressed;
		}
	}
	else
	{
		if (currentButtons[button] == 0)
		{
			return KeyStatus::JustReleased;
		}
		else
		{
			return KeyStatus::Held;
		}
	}
}
