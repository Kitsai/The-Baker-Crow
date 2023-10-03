#include <GameObject.h>
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

void GameObject::Update(float dt) {
    for(int i=0;i<components.size();i++) {
        components[i]->Update(dt);
    }
} 

void GameObject::Render() {
    for(int i=0;i<components.size();i++) {
        components[i]->Render();  
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
    if(started) cpt->Start();
}


void GameObject::RemoveComponent(Component* cpt) {
    for(int i=0; i<components.size();i++) 
        if(components[i].get() == cpt){
            components.erase(components.begin()+i);
            return;
        }  
}


Component* GameObject::GetComponent(std::string type) {
    for(int i=0;i<components.size();i++) 
        if(components[i]->Is(type))
            return (Component*)components[i].get(); 
    return nullptr;
}

std::vector<Component*> GameObject::GetComponents(std::string type) {
    std::vector<Component*> ret;
    for(int i=0;i<components.size();i++) {
        if(components[i]->Is(type)) {
            ret.push_back(components[i].get());
        }
    }
    return ret;
}

void GameObject::Start() {
    for(int i=0;i<components.size();i++) 
        components[i]->Start();
    started = true;   
}

void GameObject::NotifyCollision(GameObject& other) {
    for(int i=0;i<components.size();i++) components[i]->NotifyCollision(other); 
}