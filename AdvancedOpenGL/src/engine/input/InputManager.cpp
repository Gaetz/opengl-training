#include "InputManager.h"
#include <cstring>

InputManager::InputManager():
	inputState(),
	isCursorDisplayed(false),
	controller(nullptr)
{}

InputManager::~InputManager()
{}

void InputManager::init(int screenWidth, int screenHeight)
{
	windowWidth = screenWidth;
	windowHeight = screenHeight;

	// Keyboard
	// Assign current state pointer
	inputState.keyboardState.currentValue = SDL_GetKeyboardState(nullptr);
	// Clear previous state memory
	memset(inputState.keyboardState.previousValue, 0, SDL_NUM_SCANCODES);

	// Mouse (just set everything to 0)
	inputState.mouseState.currentButtons = 0;
	inputState.mouseState.previousButtons = 0;

	// Get the connected controller, if it exists
	controller = SDL_GameControllerOpen(0);
	// Initialize controller state
	inputState.controllerState.isConnected = (controller != nullptr);
	memset(inputState.controllerState.currentButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
	memset(inputState.controllerState.previousButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
}

void InputManager::clear()
{
	if (controller != nullptr)
	{
		SDL_GameControllerClose(controller);
	}
}

void InputManager::prepareForUpdate()
{
	// Keyboard: Copy current state to previous
	memcpy(inputState.keyboardState.previousValue, inputState.keyboardState.currentValue, SDL_NUM_SCANCODES);
	// Mouse
	inputState.mouseState.previousButtons = inputState.mouseState.currentButtons;
	inputState.mouseState.scrollWheel = Vector2::zero;
	// Controller
	memcpy(inputState.controllerState.previousButtons, inputState.controllerState.currentButtons, SDL_CONTROLLER_BUTTON_MAX);
}

void InputManager::update()
{
		// Mouse
	int x = 0, y = 0;
	if (inputState.mouseState.isRelativeMode)
	{
		inputState.mouseState.currentButtons = SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		inputState.mouseState.currentButtons = SDL_GetMouseState(&x, &y);
	}

	inputState.mouseState.position.x = static_cast<float>(x);
	inputState.mouseState.position.y = static_cast<float>(y);
	if (!inputState.mouseState.isRelativeMode)
	{
		// We want mouseState coordinates to be between minus half the screen's size and plus half the screen size
		inputState.mouseState.position.x -= windowWidth * 0.5f;
		inputState.mouseState.position.y = windowHeight * 0.5f - inputState.mouseState.position.y;
	}

	// Controller
	// Buttons
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
	{
		inputState.controllerState.currentButtons[i] = SDL_GameControllerGetButton(controller, SDL_GameControllerButton(i));
	}

	// Triggers
	inputState.controllerState.leftTrigger = filter1D(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
	inputState.controllerState.rightTrigger = filter1D(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT));

	// Sticks
	x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	y = -SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
	inputState.controllerState.leftStick = filter2D(x, y);

	x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
	y = -SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
	inputState.controllerState.rightStick = filter2D(x, y);
}

bool InputManager::pollInputs()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	bool isRunning = true;
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			inputState.mouseState.scrollWheel = Vector2(
			static_cast<float>(event.wheel.x),
			static_cast<float>(event.wheel.y));
		break;
		default:
			break;
	}
	return isRunning;
}

const InputState& InputManager::getState() const
{
    return inputState;
}


void InputManager::setMouseCursor(bool isCursorDisplayedP)
{
	isCursorDisplayed = isCursorDisplayedP;
	if (isCursorDisplayedP)
	{
		SDL_ShowCursor(SDL_TRUE);
	}
	else
	{
		SDL_ShowCursor(SDL_FALSE);
	}
}

void InputManager::setMouseRelativeMode(bool isMouseRelativeOnP)
{
	SDL_bool set = isMouseRelativeOnP ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	inputState.mouseState.isRelativeMode = isMouseRelativeOnP;
}


float InputManager::filter1D(int input)
{
	const int deadZone = CONTROLLER_DEAD_ZONE_1D;
	const int maxValue = CONTROLLER_MAX_VALUE;
	float retVal = 0.0f;

	int absValue = input > 0 ? input : -input;
	if (absValue > deadZone)
	{
		// Compute fractional value between dead zone and max value
		retVal = static_cast<float>(absValue - deadZone) / (maxValue - deadZone);
		// Make sure sign matches original value
		retVal = input > 0 ? retVal : -1.0f * retVal;
		// Clamp between -1.0f and 1.0f
		retVal = Maths::clamp(retVal, -1.0f, 1.0f);
	}

	return retVal;
}

Vector2 InputManager::filter2D(int inputX, int inputY)
{
	const float deadZone = CONTROLLER_DEAD_ZONE_2D;
	const float maxValue = CONTROLLER_MAX_VALUE;

	Vector2 dir;
	dir.x = static_cast<float>(inputX);
	dir.y = static_cast<float>(inputY);
	float length = dir.length();

	// If length < deadZone, should be no input
	if (length < deadZone)
	{
		dir = Vector2::zero;
	}
	else
	{
		// Calculate fractional value between dead zone and max value circles
		float f = (length - deadZone) / (maxValue - deadZone);
		// Clamp f between 0.0f and 1.0f
		f = Maths::clamp(f, 0.0f, 1.0f);
		// Normalize the vector, and then scale it to the fractional value
		dir *= f / length;
	}

	return dir;
}
