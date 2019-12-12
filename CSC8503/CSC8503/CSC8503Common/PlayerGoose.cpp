#include "PlayerGoose.h"
#include "PositionConstraint.h"
#include "GameWorld.h"
using namespace NCL::CSC8503;

PlayerGoose::PlayerGoose(string objectName) {
	score = 0;
	carryApple = false;
	name = objectName;
	isActive = true;
	
	boundingVolume = nullptr;
	physicsObject = nullptr;
	renderObject = nullptr;
	networkObject = nullptr;
	world = nullptr;
	constraint = nullptr;
}

void PlayerGoose::OnCollisionBegin(GameObject* otherObject) {
	if (otherObject->GetName() == "apple") {
		if (!carryApple) {
			constraint = new PositionConstraint((GameObject*)this, otherObject, 2.0f);
			otherObject->GetGameWorld()->AddConstraint(constraint);
			carryApple = true;
		}
	}
	if (otherObject->GetName() == "ParkKeeper") {
		otherObject->GetTransform().SetWorldPosition(Vector3(50, 5, 50));
		std::cout << "keeper goose" << std::endl;
		if (this->GetCarry()) {
			world->RemoveConstraint(this->GetConstraint());
			this->SetCarry(false);
		}
		this->GetTransform().SetWorldPosition(Vector3(0, 2, 0));
	}
}

void PlayerGoose::OnCollisionEnd(GameObject* otherObject) {
	//std::cout << "end" << std::endl;
}