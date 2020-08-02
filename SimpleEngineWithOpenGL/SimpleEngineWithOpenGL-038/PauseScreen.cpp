#include "PauseScreen.h"
#include "Game.h"

PauseScreen::PauseScreen() : UIScreen()
{
	Game::instance().setState(GameState::Pause);
	Game::instance().getInputSystem().setMouseRelativeMode(false);
	setTitle("Pause");
}

PauseScreen::~PauseScreen()
{
	Game::instance().setState(GameState::Gameplay);
	Game::instance().getInputSystem().setMouseRelativeMode(true);
}

void PauseScreen::processInput(const InputState& inputState)
{
	UIScreen::processInput(inputState);
	if (inputState.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		close();
	}
}

