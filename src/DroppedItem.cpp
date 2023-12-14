#include "DroppedItem.h"

#include "Game.h"
#include "TukiOW.h"

DroppedItem::DroppedItem(GameObject& associated, FoodItemType itemType) : Component(associated), itemType(itemType), active(false), timeToActivate(DROPS_ACTIVATE_DELAY) {
    associated.AddComponent(new Sprite(associated, "resources/img/ingredients/"+foodItemTypeToString[itemType]+".png"));
    associated.AddComponent(new Collider(associated));
}

DroppedItem::~DroppedItem() {

}

void DroppedItem::Update(float dt) {
    timeToActivate -= dt;
    if(timeToActivate <= 0) {
        active = true;
    }
}

void DroppedItem::Render() {

}

bool DroppedItem::Is(std::string type) {
    return type == "DroppedItem";
}

FoodItemType DroppedItem::GetItemType() {
    return itemType;
}

void DroppedItem::NotifyCollision(GameObject& other) {
    if(active && other.GetComponent("Player").lock() && GameData::hasItem[itemType].first == false) {
        GameData::hasItem[itemType].first = true;
        associated.RequestDelete();
    }
}