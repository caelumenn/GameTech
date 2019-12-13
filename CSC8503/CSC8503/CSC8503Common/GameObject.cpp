#include "GameObject.h"
#include "CollisionDetection.h"
#include "GameWorld.h"
#include "PlayerGoose.h"
using namespace NCL::CSC8503;

GameObject::GameObject(string objectName)	{
	name			= objectName;
	isActive		= true;
	boundingVolume	= nullptr;
	physicsObject	= nullptr;
	renderObject	= nullptr;
	networkObject	= nullptr;
	world			= nullptr;
}

GameObject::~GameObject()	{
	delete boundingVolume;
	delete physicsObject;
	delete renderObject;
	delete networkObject;
	//delete world;
}

bool GameObject::GetBroadphaseAABB(Vector3&outSize) const {
	if (!boundingVolume) {
		return false;
	}
	outSize = broadphaseAABB;
	return true;
}

//These would be better as a virtual 'ToAABB' type function, really...
void GameObject::UpdateBroadphaseAABB() {
	if (!boundingVolume) {
		return;
	}
	if (boundingVolume->type == VolumeType::AABB) {
		broadphaseAABB = ((AABBVolume&)*boundingVolume).GetHalfDimensions();
	}
	else if (boundingVolume->type == VolumeType::Sphere) {
		float r = ((SphereVolume&)*boundingVolume).GetRadius();
		broadphaseAABB = Vector3(r, r, r);
	}
	else if (boundingVolume->type == VolumeType::OBB) {
		Matrix3 mat = Matrix3(transform.GetWorldOrientation());
		mat = mat.Absolute();
		Vector3 halfSizes = ((OBBVolume&)*boundingVolume).GetHalfDimensions();
		broadphaseAABB = mat * halfSizes;
	}
}

void GameObject::OnCollisionBegin(GameObject* otherObject) {
	if (otherObject->GetName() == "island" && this->GetName() == "apple") {
		PlayerGoose* player = (PlayerGoose*)this->GetGameWorld()->GetPlayer();
		int score = player->GetScore();
		score += 10;
		player->SetScore(score);
		PositionConstraint* constraint = player->GetConstraint();
		world->RemoveConstraint(constraint);
		player->SetCarry(false);
		world->RemoveGameObject(this);
		GameWorld::setGameOver(true);
	}
}
