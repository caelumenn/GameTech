#pragma once
#include "GameObject.h"
#include "Ray.h"
#include "StateMachine.h"
#include "State.h"
namespace NCL {
	namespace CSC8503 {
		class ParkKeeper : public GameObject{
		public:
			ParkKeeper(string name = "");
			~ParkKeeper() {}
			void setStateMachine();
			void OnCollisionBegin(GameObject* otherObject) override;
			void OnCollisionEnd(GameObject* otherobject) override;
		protected:
			Ray* ray;
			StateMachine* keeperStateMachine;
		};
	}
}

