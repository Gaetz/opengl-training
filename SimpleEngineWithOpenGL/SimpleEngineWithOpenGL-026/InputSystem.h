#pragma once
#include "KeyboardState.h"

enum class ButtonState
{
	None,
	Pressed,
	Released, 
	Held
};

struct InputState
{
	KeyboardState keyboard;
};

class InputSystem
{
public:
	InputSystem();

	bool initialize();
	void close();

	const InputState getInputState() const { return inputState; }

	void preUpdate();
	void update();


private:
	InputState inputState;
};

