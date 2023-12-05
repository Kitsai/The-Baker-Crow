#ifndef FoodPiece_h_
#define FoodPiece_h_

#include <string>
#include <vector>
#include "Component.h"
#include "GameObject.h"
#include "items.h"

class FoodItem;

class FoodPiece : public Component {
public:
    FoodPiece(GameObject& associated, FoodItem& FoodItem);
    ~FoodPiece();
    
    void Render();
    void Update(float dt);
    void SetFoodItem(FoodItem* FoodItem);

    FoodItem* GetFoodItem();
    FoodItemType GetType();
    
    bool Lock();
    bool UnLock();
    bool IsLocked();
    bool Is(std::string type);

    void Wait();
    bool GetStatus();

    std::vector<std::vector<int>> GetForm();
    std::vector<std::weak_ptr<GameObject>> GetPieces();

    void RenderPieces();
private:
    // Attributes
    bool locked;
    bool waiting;

    FoodItem* foodItem;
    FoodItemType type;
    std::vector<std::vector<int>> form;
    std::vector<std::weak_ptr<GameObject>> pieces;
    //Methods
    void evaluateForm();
};

#endif