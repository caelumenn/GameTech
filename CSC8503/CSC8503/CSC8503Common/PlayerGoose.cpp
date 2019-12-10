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
}

void PlayerGoose::OnCollisionEnd(GameObject* otherObject) {
	//std::cout << "end" << std::endl;
}