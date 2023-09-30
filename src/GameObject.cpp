#include <GameObject.h>
#include <vector>
#include <algorithm>
#include <iostream>

/// @brief 
/// Game Object constructor. Initializes the box with all 0's and isDead as false.
GameObject::GameObject():box() {
    isDead = false;
    started = false;
    angleDeg = 0;
}

/// @brief 
/// Clears the Component vector deleting all of them.
GameObject::~GameObject() {
    components.clear();
}

/// @brief 
/// Propagates the Update for all associated Components.
/// @param dt 
/// Float refering to the Delta Time.
void GameObject::Update(float dt) {
    for(int i=0;i<components.size();i++) {
        components[i]->Update(dt);
    }
} 

/// @brief 
/// Propagates the Render for all associated Components.
void GameObject::Render() {
    for(int i=0;i<components.size();i++) {
        components[i]->Render();  
    }
}

/// @brief 
/// Getter for the isDead.
/// @return 
/// bool that says whether the object should be deleted.
bool GameObject::IsDead() {
    return isDead;
}

/// @brief 
/// Requests that the object be deleted by turning isDead true.
void GameObject::RequestDelete() {
    isDead = true;
}

/// @brief 
/// Adds component to the list of associated Components as unique pointers.
/// @param cpt 
/// A pointer to the Component that should be added.
void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
    if(started) cpt->Start();
}

/// @brief 
/// Removes a Component from the list of associated Components.
/// @param cpt 
/// Pointer to the Component to be deleted.
void GameObject::RemoveComponent(Component* cpt) {
    for(int i=0; i<components.size();i++) 
        if(components[i].get() == cpt){
            components.erase(components.begin()+i);
            return;
        }  
}

/// @brief 
/// Gets a component of desired type.
/// @param type 
/// Type of Component to be searched.
/// @return 
/// A pointer to the searched component. If not found return nullptr.
Component* GameObject::GetComponent(std::string type) {
    for(int i=0;i<components.size();i++) 
        if(components[i]->Is(type))
            return (Component*)components[i].get(); 
    return nullptr;
}

/// @brief 
/// Verify if the object has a class that identify it as an enemy that should explode. 
/// @return 
/// true if it an explodable entity. False on the contrary.
bool GameObject::IsEntity() {
    // No momento so procura uma face mas posteriormente procurar todos as classes que herdam de um tipo entity
    for(int i=0;i<components.size();i++) 
        if(components[i]->Is("Face"))
            return true;
    return false; 
}

void GameObject::Start() {
    for(int i=0;i<components.size();i++) 
        components[i]->Start();
    started = true;   
}

void GameObject::NotifyCollision(GameObject& other) {
    for(int i=0;i<components.size();i++) components[i]->NotifyCollision(other); 
}