#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include "Input_KeyboardState.h"
#include "Input_MouseState.h"
#include "Input_ControllerState.h"

struct InputState
{
	KeyboardState keyboardState;
	MouseState mouseState;
	ControllerState controllerState;
};

#endif