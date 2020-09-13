#ifndef INPUT_MOUSE_STATE_H
#define INPUT_MOUSE_STATE_H

#include "Input_KeyStatus.h"
#include "../maths/Vector2.h"

#ifdef __linux__
#include <SDL2/SDL_stdinc.h>
#elif _WIN32
#include <SDL_stdinc.h>
#endif

class MouseState
{
	friend class InputManager;
public:
	const Vector2& getPosition() const { return position; }
	bool getButtonValue(int button) const;
	enum class KeyStatus getButtonState(int button) const;
	const Vector2& getScrollWheel() const { return scrollWheel; }
	bool isRelativeModeOn() const { return isRelativeMode; }

private:
	Vector2 position;
	Uint32 currentButtons;
	Uint32 previousButtons;
	Vector2 scrollWheel;
	bool isRelativeMode;
};


#endif