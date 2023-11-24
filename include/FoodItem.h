#ifndef FoodItem_h_
#define FoodItem_h_

#include <string>
#include "Component.h"
#include "items.h"

class FoodPiece;
class FoodItem : public Component{
    public:
        FoodItem(GameObject& associated, FoodItemType type);        
        
        void Increase();
        void Decrease();
        void Render();
        void Update(float dt);
        
        bool Is(std::string type);

        FoodItemType GetType();
        FoodPiece*  GetFoodPiece();
    
    private:
        int amount;
        FoodItemType type;
        FoodPiece* foodPiece;  
};
#endif