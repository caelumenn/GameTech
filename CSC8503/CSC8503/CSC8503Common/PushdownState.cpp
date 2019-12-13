#include "PushdownState.h"
#include "../../Common/window.h"

using namespace NCL::CSC8503;

PushdownState::PushdownState()
{
}


PushdownState::~PushdownState()
{
}

PushdownResult MenuState::PushdownUpdate(MenuState** pushResult) {
	if (this->type == MenuType::mainMenu) {
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE)) {
			(*pushResult)->type = MenuType::play; //Play single player game
			return PushdownResult::Push;
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::ESCAPE)) {
			(*pushResult)->type = MenuType::exit;
			return PushdownResult::Push; // Exit the game!
		}
	}

	if (this->type == MenuType::play) {
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P)) {
			(*pushResult)->type = MenuType::pause; // pause the game
			return PushdownResult::Push;
		}
		if (GameWorld::getGameOver()) {
			(*pushResult)->type = MenuType::gameOver;
			return PushdownResult::Push;
		}
	}

	if (this->type == MenuType::pause) {
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P)) {
			return PushdownResult::Pop; // Continue the game
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::ESCAPE)) {
			(*pushResult)->type = MenuType::exit;
			return PushdownResult::Push; // Exit the game
		}
	}

	if (this->type == MenuType::gameOver) {
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::R)) {
			(*pushResult)->type = MenuType::mainMenu; //Play single player game
			return PushdownResult::Push;
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::ESCAPE)) {
			(*pushResult)->type = MenuType::exit;
			return PushdownResult::Push; // Exit the game!
		}
	}
	//Should have a game over state
	return PushdownResult::NoChange;
}