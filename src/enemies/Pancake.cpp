#include "enemies/Pancake.h"
#include <cstdlib>

Pancake::Pancake(GameObject& assoc, int hp): Enemy(assoc,hp) {
    assoc.AddComponent(new Sprite(assoc, "../../resources/img/pancake_idle.png"));

}

Pancake::~Pancake() {

}

bool Pancake::Is(std::string type) {
    return type == "Pancake" || Enemy::Is(type);
}

void Pancake::SetState(EnemyState state) {
    this->state = state;

    switch (state) {
        case MOVING:
            moveTarget = associated.box.GetCenter() + Vec2(rand()%500,rand()%500);
            break;
        case ATTACKING:
            Attk();
            break;
        case IDLE:
            idleTime = rand()%5001*0.001F + 2;
            speed = 0;
            break;
        deffault:
            break;
    }
}

