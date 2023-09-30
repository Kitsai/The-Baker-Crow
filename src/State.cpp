#include <State.h>

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

	for(int i=0;i<objectArray.size();i++) {
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
    for(int i=0;i<objectArray.size();i++) objectArray[i]->Start();
}

void State::UpdateArray(float dt) {
    for(int i=0;i<objectArray.size();i++) objectArray[i]->Update(dt);
}

void State::RenderArray() {
    for(int i=0;i<objectArray.size();i++) objectArray[i]->Render();
}