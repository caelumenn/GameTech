#pragma once
#include <stack>
#include "PushdownState.h"

namespace NCL {
	namespace CSC8503 {
		class MenuState;

		class PushdownMachine
		{
		public:
			PushdownMachine() {}
			~PushdownMachine() {}

			virtual void Update() {}
		};

		class MenuPushdownMachine : public PushdownMachine
		{
		public:
			MenuPushdownMachine();
			~MenuPushdownMachine();

			void Update();

			MenuType GetActiveStateType();

		protected:
			MenuState* activeState;

			std::stack<MenuState*> stateStack;
		};

	}
}
