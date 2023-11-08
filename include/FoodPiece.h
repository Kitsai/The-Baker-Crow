#ifndef FoodPiece_h_
#define FoodPiece_h_

#include <string>
#include <vector>
#include "Component.h"

class Item;

class FoodPiece : public Component {
public:
    FoodPiece(GameObject& associated, std::string type);
    ~FoodPiece();
    
    void Render();
    void Update(float dt);
    void SetItem(Item* item);

    Item* GetItem();
    std::string GetType();
    
    bool Lock();
    bool UnLock();
    bool Is(std::string type);

    std::vector<std::vector<int>> GetForm();
    
private:
    // Attributes
    bool locked;

    Item* item;
    std::string type;
    std::vector<std::vector<int>> form;
    //Methods
    void evaluateForm();
};

#endif
