#ifndef FoodItem_h_
#define FoodItem_h_

#include <string>
#include "Component.h"

class FoodPiece;
class FoodItem : public Component{
    public:
        FoodItem(GameObject& associated, std::string type);        
        
        void Increase();
        void Decrease();
        void Render();
        void Update(float dt);
        
        std::string GetType();
        FoodPiece*  GetFoodPiece() const;
    
    private:
        int amount;
        std::string type;
        FoodPiece* foodPiece;  
};
#endif