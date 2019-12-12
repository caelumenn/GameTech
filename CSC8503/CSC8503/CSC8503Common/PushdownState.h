#pragma once
#include "State.h"

namespace NCL {
	namespace CSC8503 {
		enum class MenuType {
			init,
			mainMenu,
			play,
			pause,
			gameOver,
			exit
		};
		enum PushdownResult {
			Push, Pop, NoChange
		};
		class PushdownState : public State
		{
		public:

			PushdownState();
			~PushdownState();

			PushdownResult PushdownUpdate(PushdownState** pushResult);

			virtual void OnAwake() {} //By default do nothing
			virtual void OnSleep() {} //By default do nothing
		};

		class MenuState : public PushdownState {
		public:
			MenuState(MenuType type = MenuType::init) {
				this->type = type;
			}
			~MenuState() {}

			PushdownResult PushdownUpdate(MenuState** pushResult);

			void Update() {}

			MenuType GetType() {
				return type;
			}

			void SetType(MenuType type) {
				this->type = type;
			}

		private:
			MenuType type;
		};
	}
}

