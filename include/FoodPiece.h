#ifndef FoodPiece_h_
#define FoodPiece_h_

#include <string>
#include <vector>
#include "Component.h"
#include "GameObject.h"

class FoodItem;

class FoodPiece : public Component {
public:
    FoodPiece(GameObject& associated, FoodItem& FoodItem);
    ~FoodPiece();
    
    void Render();
    void Update(float dt);
    void SetFoodItem(FoodItem* FoodItem);

    FoodItem* GetFoodItem();
    std::string GetType();
    
    bool Lock();
    bool UnLock();
    bool Is(std::string type);

    std::vector<std::vector<int>> GetForm();
    void RenderPieces();
private:
    // Attributes
    bool locked;

    FoodItem* foodItem;
    std::string type;
    std::vector<std::vector<int>> form;
    std::vector<std::weak_ptr<GameObject>> pieces;
    //Methods
    void evaluateForm();
};

#endif