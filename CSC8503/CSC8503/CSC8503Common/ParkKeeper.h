#pragma once
#include "GameObject.h"
#include "Ray.h"
#include "StateMachine.h"
#include "State.h"
#include "StateTransition.h"
#include "NavigationGrid.h"
namespace NCL {
	namespace CSC8503 {
		class ParkKeeper : public GameObject{
		public:
			ParkKeeper(string name = "");
			~ParkKeeper() {}
			StateMachine* keeperStateMachine;
			float distance;
			void setStateMachine();
			void pathFinding();
			//void OnCollisionBegin(GameObject* otherObject) override;
			//void OnCollisionEnd(GameObject* otherobject) override;
		protected:
			vector<Vector3>* pathNodes;
		};
	}
}

