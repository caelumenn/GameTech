#include "ParkKeeper.h"
using namespace NCL::CSC8503;

ParkKeeper::ParkKeeper(string objectName) {
	name = objectName;
	isActive = true;
	boundingVolume = nullptr;
	physicsObject = nullptr;
	renderObject = nullptr;
	networkObject = nullptr;
	world = nullptr;
}

void ParkKeeper::setStateMachine() {
	keeperStateMachine = new StateMachine();

	StateFunc IdleFunc = [](void* data) {
		std::cout << "In State Idle!" << std::endl;
	};

	StateFunc PatrolFunc = [](void* data) {
		std::cout << "In State Patrol!" << std::endl;
	};

	StateFunc ChaseFunc = [](void* data) {
		std::cout << "In State Chase!" << std::endl;
	};
}