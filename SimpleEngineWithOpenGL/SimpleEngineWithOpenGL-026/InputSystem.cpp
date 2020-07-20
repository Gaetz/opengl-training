#include "InputSystem.h"
#include <SDL_keyboard.h>
#include <cstring>

InputSystem::InputSystem() : inputState()
{
}

bool InputSystem::initialize()
{
	// Keyboard
	// Assign current state pointer
	inputState.keyboard.currentState = SDL_GetKeyboardState(nullptr);
	// Clear previous state memory
	memset(inputState.keyboard.previousState, 0, SDL_NUM_SCANCODES);

	return true;
}

void InputSystem::close()
{
}

void InputSystem::preUpdate()
{
	// Copy current state to previous
	// Keyboard
	memcpy(inputState.keyboard.previousState, inputState.keyboard.currentState, SDL_NUM_SCANCODES);
}

void InputSystem::update()
{
}
