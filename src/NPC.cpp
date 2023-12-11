#include "NPC.h"

NPC::NPC(GameObject& associated, std::string file) : Component(associated) {
    this->file = file;
    Sprite* sprite = new Sprite(associated, file);
    sprite->SetScale(2.0f, 2.0f);
    associated.AddComponent(sprite);
}

NPC::~NPC() {}

void NPC::Update(float dt) {}

void NPC::Render() {}

bool NPC::Is(std::string type) {
    return (type == "NPC");
}