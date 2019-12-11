#include "ParkKeeper.h"
#include "GameWorld.h"
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
	distance = (this->GetGameWorld()->GetPlayer()->GetTransform().GetWorldPosition() - 
		this->GetTransform().GetWorldPosition()).Length();

	StateFunc IdleFunc = [](void* data) {
		ParkKeeper* p = (ParkKeeper*)data;
		p->distance = (p->GetGameWorld()->GetPlayer()->GetTransform().GetWorldPosition() -
			p->GetTransform().GetWorldPosition()).Length();
		std::cout << "In State Idle!" << std::endl;
	};

	StateFunc ChaseFunc = [](void* data) {
		ParkKeeper* p = (ParkKeeper*)data;
		p->distance = (p->GetGameWorld()->GetPlayer()->GetTransform().GetWorldPosition() -
			p->GetTransform().GetWorldPosition()).Length();
		p->pathFinding();
		std::cout << "In State Chase!" << std::endl;
	};

	GenericState* idleState = new GenericState(IdleFunc, (void*)this);
	GenericState* chaseState = new GenericState(ChaseFunc, (void*)this);
	keeperStateMachine->AddState(idleState);
	keeperStateMachine->AddState(chaseState);

	GenericTransition<float&, float>* transitionA =
		new GenericTransition <float&, float>(GenericTransition<float&, float>::LessThanTransition, distance, 100, idleState, chaseState);
	GenericTransition<float&, float>* transitionB =
		new GenericTransition <float&, float>(GenericTransition<float&, float>::GreaterThanTransition, distance, 120, chaseState, idleState);

	keeperStateMachine->AddTransition(transitionA);
	keeperStateMachine->AddTransition(transitionB);
}

void ParkKeeper::pathFinding() {
	delete pathNodes;
	NavigationGrid grid("grid.txt");
	pathNodes = new vector<Vector3>;

	NavigationPath outPath;

	Vector3 startPos = this->GetTransform().GetWorldPosition();
	Vector3 endPos = this->GetGameWorld()->GetPlayer()->GetTransform().GetWorldPosition();
	startPos.x = 100.0 - startPos.x;
	startPos.z = 80.0 - startPos.z;
	//startPos.y = 0;
	endPos.x = 100.0 - endPos.x;
	endPos.z = 80.0 - endPos.z;
	//endPos.y = 0;

	bool found = grid.FindPath(startPos, endPos, outPath);
	std::cout << found << std::endl;

	Vector3 pos;
	while (outPath.PopWaypoint(pos)) {
		pathNodes->push_back(pos);
	}

	for (int i = 1; i < pathNodes->size(); ++i) {
		Vector3 a = pathNodes->at(i-1);
		Vector3 b = pathNodes->at(i);

		a.x = -(a.x - 100.0);
		a.y = 3;
		a.z = -(a.z- 80.0);
		b.x = -(b.x- 100.0);
		b.y = 3;
		b.z = -(b.z - 80.0);
		Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
	}
}