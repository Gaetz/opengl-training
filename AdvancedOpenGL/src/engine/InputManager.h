#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "InputState.h"

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	// Setup initial input state
	void init(int screenWidth, int screenHeight);

	// Clear input manager before shutting down
	void clear();

	// Set input state before polling
	void prepareForUpdate();

	// Update
	void update();

	// Poll inputs and return quit status
	bool pollInputs();

	// Acces general state of inputs
	const InputState& getState() const;

	bool getIsCursorDisplayed() const { return isCursorDisplayed; }
	void setMouseCursor(bool isCursorDisplayedP);
	void setMouseRelativeMode(bool isMouseRelativeOnP);

private:
	float filter1D(int input);
	Vector2 filter2D(int inputX, int inputY);

	// General state of inputs
	InputState inputState;

	bool isCursorDisplayed;
	SDL_GameController* controller;

	int windowWidth;
	int windowHeight;
};

constexpr int CONTROLLER_DEAD_ZONE_1D = 250;
constexpr float CONTROLLER_DEAD_ZONE_2D = 8000.0f;
constexpr int CONTROLLER_MAX_VALUE = 30000;

#endif