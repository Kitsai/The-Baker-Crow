#include "Component.h"
#include <algorithm>

/// @brief 
/// Default constructor for components that initializes the associated game object.
/// @param assoc 
/// A reference to the Game Object this Component is part of.
Component::Component(GameObject& assoc): associated(assoc) {

}

Component::~Component() {
    
}

void Component::Start() {
    
}

void Component::NotifyCollision(GameObject& other) {
    
}