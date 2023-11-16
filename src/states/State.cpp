#include "states/State.h"

#include "../Collision.cpp"

State::State() {
    popRequested = false;
    quitRequested = false;
    started = false;
}

State::~State() {
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> goPtr(go);
	objectArray.push_back(goPtr);
	if(started) {
		goPtr->Start();
	}
	std::weak_ptr<GameObject> goWPtr = goPtr;

	return goWPtr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    std::weak_ptr<GameObject> retPrt;

	for(std::vector<int>::size_type i=0;i<objectArray.size();i++) {
		if(objectArray[i].get() == go) {
			retPrt = objectArray[i];
			break;
		}
	}
	return retPrt;
}

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for(std::vector<int>::size_type i=0;i<objectArray.size();i++) objectArray[i]->Start();
}

void State::UpdateArray(float dt) {
    for(std::vector<int>::size_type i=0;i<objectArray.size();i++) objectArray[i]->Update(dt);
}

void State::RenderArray() {
    for(std::vector<int>::size_type i=0;i<objectArray.size();i++) objectArray[i]->Render();
}

void State::CheckCollisions() {
	for(std::vector<int>::size_type i=0;i<objectArray.size();i++) {
		Collider* colliderA = (Collider*)objectArray[i]->GetComponent("Collider").get();

		if(colliderA != nullptr && colliderA->active) {
			for(std::vector<int>::size_type j=i;j<objectArray.size();++j) {
				Collider* colliderB = (Collider*)objectArray[j]->GetComponent("Collider").get();
				if(	colliderB != nullptr 
					&& colliderB->active 
					&& Collision::IsColliding(colliderA->box, colliderB->box,objectArray[i]->angleDeg,objectArray[j]->angleDeg)
				) {
					objectArray[i]->NotifyCollision(*objectArray[j]);
					objectArray[j]->NotifyCollision(*objectArray[i]);
				}
			}
		}
	}
}

void State::DeleteObjects() {
	for(std::vector<int>::size_type i=0;i<objectArray.size();i++) 
		if(objectArray[i]->IsDead()) 
			objectArray.erase(objectArray.begin()+i);
}