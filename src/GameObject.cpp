#include "GameObject.h"
#include "Component.h"
#include <vector>
#include <algorithm>
#include <iostream>

GameObject::GameObject() :  isDead(false), started(false), box(0, 0, 0, 0), angleDeg(0) {

}

GameObject::~GameObject() {
    componentArray.clear();
}

void GameObject::Start(){
    for (auto& component : componentArray){
        component->Start();
    }
    started = true;
}


void GameObject::Update(float dt) {
    for (std::vector<int>::size_type i = 0; i < componentArray.size(); i++){
        componentArray[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (std::vector<int>::size_type i = 0; i < componentArray.size(); i++){
        componentArray[i]->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::UnrequestDelete() {
    isDead = false;
}

std::weak_ptr<Component> GameObject::AddComponent(Component* cpt) {
    std::shared_ptr<Component> sharPtr(cpt);
    componentArray.emplace_back(sharPtr);
    if (started) {
        sharPtr->Start();
    }
    std::weak_ptr<Component> cptWPtr = sharPtr;
    return cptWPtr;
}

void GameObject::RemoveComponent(Component* cpt) {
    for (std::vector<int>::size_type i = 0; i < componentArray.size(); i++) {
        if (componentArray[i].get() == cpt) {
            componentArray.erase(componentArray.begin() + i);
            break;
        }
    }
}

std::weak_ptr<Component> GameObject::GetComponent(std::string type) {
    for (std::vector<int>::size_type i = 0; i < componentArray.size(); i++) {
        if (componentArray[i]->Is(type)) {
            return componentArray[i];
        }
    }

    return std::weak_ptr<Component>();
}

std::vector<Component*> GameObject::GetComponents(std::string type) {
    std::vector<Component*> ret;
    for(std::vector<int>::size_type i=0;i<componentArray.size();i++) {
        if(componentArray[i]->Is(type)) {
            ret.push_back(componentArray[i].get());
        }
    }
    return ret;
}

void GameObject::NotifyCollision(GameObject& other) {
    for(std::vector<int>::size_type i=0;i<componentArray.size();i++) componentArray[i]->NotifyCollision(other); 
}