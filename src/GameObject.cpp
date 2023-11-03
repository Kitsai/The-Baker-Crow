#include "GameObject.h"
#include <vector>
#include <algorithm>
#include <iostream>

GameObject::GameObject():box() {
    isDead = false;
    started = false;
    angleDeg = 0;
}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Start(){
    for (auto& component : components){
        component->Start();
    }
    started = true;
}


void GameObject::Update(float dt) {
    for (std::vector<int>::size_type i = 0; i < components.size(); i++){
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (std::vector<int>::size_type i = 0; i < components.size(); i++){
        components[i]->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(std::shared_ptr<Component> cpt){
    components.emplace_back(cpt);
    if (started) {
        cpt->Start();
    }
}


void GameObject::RemoveComponent(std::shared_ptr<Component> cpt){
    for (std::vector<int>::size_type i = 0; i < components.size(); i++){
        if (components[i] == cpt){
            components.erase(components.begin() + i);
        }
    }
}


std::shared_ptr<Component> GameObject::GetComponent(std::string type){
    for (std::vector<int>::size_type i = 0; i < components.size(); i++){
        if (components[i]->Is(type))
        {
            return components[i];
        }
    }

    return nullptr;
}

std::vector<Component*> GameObject::GetComponents(std::string type) {
    std::vector<Component*> ret;
    for(std::vector<int>::size_type i=0;i<components.size();i++) {
        if(components[i]->Is(type)) {
            ret.push_back(components[i].get());
        }
    }
    return ret;
}


void GameObject::NotifyCollision(GameObject& other) {
    for(std::vector<int>::size_type i=0;i<components.size();i++) components[i]->NotifyCollision(other); 
}