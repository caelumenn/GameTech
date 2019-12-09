#include "PlayerGoose.h"
#include "PositionConstraint.h"
#include "GameWorld.h"
using namespace NCL::CSC8503;
//class GameWorld;

PlayerGoose::PlayerGoose(string objectName) {
	name = objectName;
	isActive = true;
	boundingVolume = nullptr;
	physicsObject = nullptr;
	renderObject = nullptr;
	networkObject = nullptr;
}

void PlayerGoose::OnCollisionBegin(GameObject* otherObject) {
	if (otherObject->GetName() == "apple") {
		std::cout << "start" << std::endl;
		PositionConstraint* constraint = new PositionConstraint((GameObject*)this, otherObject, 5.0f);
	    otherObject->GetGameWorld()->AddConstraint(constraint);
	}
}

void PlayerGoose::OnCollisionEnd(GameObject* otherObject) {
	std::cout << "end" << std::endl;
}