#include "PlayerGoose.h"
using namespace NCL::CSC8503;

PlayerGoose::PlayerGoose(string objectName) {
	name = objectName;
	isActive = true;
	boundingVolume = nullptr;
	physicsObject = nullptr;
	renderObject = nullptr;
	networkObject = nullptr;
}