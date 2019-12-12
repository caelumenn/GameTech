#pragma once
#include "GameObject.h"
#include "Ray.h"
#include "StateMachine.h"
#include "State.h"
#include "StateTransition.h"
#include "NavigationGrid.h"
#include "../../Common/GameTimer.h"
#include "PlayerGoose.h"
namespace NCL {
	namespace CSC8503 {
		class ParkKeeper : public GameObject{
		public:
			ParkKeeper(string name = "");
			~ParkKeeper() {}

			bool firstTime;
			float distance;
			float deltaTime;
			bool findPath;
			GameTimer* timer;
			StateMachine* keeperStateMachine;
			Vector3 playerPrePos;
			vector<Vector3>* pathNodes;
			vector<Vector3>::iterator nowDes;

			void setStateMachine();
			void pathFinding();
			void Display();
			void ChasePlayer();
			void SetPlayer(PlayerGoose* p) {
				player = p;
				SetPlayerPrePos();
			}
			void SetPlayerPrePos() {
				playerPrePos = player->GetTransform().GetWorldPosition();
			}
			void OnCollisionBegin(GameObject* otherObject) override;
			//void OnCollisionEnd(GameObject* otherobject) override;
		protected:
			PlayerGoose* player;
		};
	}
}

