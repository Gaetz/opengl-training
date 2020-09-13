#include "Input_MouseState.h"
#include "InputManager.h"
#include <SDL_mouse.h>

bool MouseState::getButtonValue(int button) const
{
	return (SDL_BUTTON(button) & currentButtons) == 1;
}

KeyStatus MouseState::getButtonState(int button) const
{
	int mask = SDL_BUTTON(button);
	if ((mask & previousButtons) == 0)
	{
		if ((mask & currentButtons) == 0)
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
		if ((mask & currentButtons) == 0)
		{
			return KeyStatus::JustReleased;
		}
		else
		{
			return KeyStatus::Held;
		}
	}
}
