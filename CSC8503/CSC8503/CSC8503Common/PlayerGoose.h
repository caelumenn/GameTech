#pragma once
#include "GameObject.h"
#include "./PositionConstraint.h"
namespace NCL {
	namespace CSC8503 {
		class GameWorld;
		class PlayerGoose :public GameObject {
		public:
			PlayerGoose(string name = "");
			~PlayerGoose() {}
			void OnCollisionBegin(GameObject* otherObject) override;
			void OnCollisionEnd(GameObject* otherobject) override;
			void SetScore(int s) { score = s; }
			int GetScore() { return score; }
			void SetCarry(bool b) { carryApple = b; }
			bool GetCarry() { return carryApple; }
			PositionConstraint* GetConstraint() { return constraint; }
		protected:
			int score;
			bool carryApple;
			PositionConstraint* constraint;
		};
	}
}
