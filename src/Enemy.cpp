#include <Enemy.h>

Enemy::Enemy(GameObject& associated): Component(associated) {

}

/// @brief 
/// Returns whether the object is of a certain type.
/// @param type 
/// Type to be checked.
/// @return 
/// True if type matches with the passed argument.
bool Enemy::Is(std::string type) {
    if(type == "Enemy") 
        return true;
    else
        return false; 
}