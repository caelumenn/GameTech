#include "PushdownMachine.h"
#include "PushdownState.h"
using namespace NCL::CSC8503;

MenuPushdownMachine::MenuPushdownMachine()
{
	activeState = new MenuState(MenuType::mainMenu);
}

MenuPushdownMachine::~MenuPushdownMachine()
{
	delete activeState;
}

MenuType MenuPushdownMachine::GetActiveStateType() {
	return activeState->GetType();
}

void MenuPushdownMachine::Update() {
	if (activeState) {
		MenuState* newState = new MenuState;
		PushdownResult result = activeState->PushdownUpdate(&newState);

		switch (result) {
			case PushdownResult::Pop: {
				activeState->OnSleep();
				stateStack.pop();
				if (stateStack.empty()) {
					activeState = nullptr; //??????
				}
				else {
					activeState = stateStack.top();
					//activeState->OnAwake();
				}
			}break;
			case PushdownResult::Push: {
				//activeState->OnSleep();
				stateStack.push(newState);
				activeState = stateStack.top();
				//newState->OnAwake();
			}break;
		}
	}
}