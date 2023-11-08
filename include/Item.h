#ifndef Item_h_
#define Item_h_

#include <string>
class FoodPiece;
class Item{
    public:
        Item(std::string type);        
        
        void Increase();
        void Decrease();
        
        void SetFoodPiece(FoodPiece* foodPiece);
        FoodPiece* GetFoodPiece() const;
    
    private:
        int amount;
        std::string type;
        FoodPiece* foodPiece;
        
};
#endif