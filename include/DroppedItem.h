#ifndef DroppedItem_h_
#define DroppedItem_h_

#include "Component.h"
#include "items.h"

class DroppedItem: public Component {
    public:
        DroppedItem(GameObject& associated, FoodItemType itemType);
        ~DroppedItem();

        void Update(float dt);
        void Render();
        bool Is(std::string type);

        FoodItemType GetItemType();
        bool IsActive();

        void NotifyCollision(GameObject& other);

    private:
        FoodItemType itemType;
        bool active;
        float timeToActivate;
};

#endif