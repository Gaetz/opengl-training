#include "Input_KeyboardState.h"

bool KeyboardState::getKeyValue(SDL_Scancode keyCode) const
{
	return currentValue[keyCode] == 1;
}

KeyStatus KeyboardState::getKeyState(SDL_Scancode keyCode) const
{
	if (previousValue[keyCode] == 0)
	{
		if (currentValue[keyCode] == 0)
		{
			return KeyStatus::None;
		}
		else
		{
			return KeyStatus::JustPressed;
		}
	}
	else // Prev state must be 1
	{
		if (currentValue[keyCode] == 0)
		{
			return KeyStatus::JustReleased;
		}
		else
		{
			return KeyStatus::Held;
		}
	}
}

bool KeyboardState::isUp(SDL_Scancode keyCode) const
{
	return !getKeyValue(keyCode);
}

bool KeyboardState::isFree(SDL_Scancode keyCode) const
{
	return getKeyState(keyCode) == KeyStatus::None;
}

bool KeyboardState::isJustPressed(SDL_Scancode keyCode) const
{
	return getKeyState(keyCode) == KeyStatus::JustPressed;
}

bool KeyboardState::isDown(SDL_Scancode keyCode) const
{
	return getKeyValue(keyCode);
}

bool KeyboardState::isHeld(SDL_Scancode keyCode) const
{
	return getKeyState(keyCode) == KeyStatus::Held;
}

bool KeyboardState::isJustReleased(SDL_Scancode keyCode) const
{
	return getKeyState(keyCode) == KeyStatus::JustReleased;
}