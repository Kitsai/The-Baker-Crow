#ifndef PuzzleState_h_
#define PuzzleState_h_

#include "Game.h"
#include "State.h"
#include "FoodItem.h"
#include "FoodPiece.h"
#include "FoodPuzzle.h"
#include "selectors/PuzzleSelector.h"
#include <type_traits>

enum class Direction {
    Up,
    Down,
    Load
};

class PuzzleState: public State {
    public:
        PuzzleState(int puzzleNumber);
        ~PuzzleState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();    
        void LoadSelector();    
    private:
        FoodPuzzle* puzzle;
        void LoadMap();
        void CreatePiece();
        void UpdateSelector(Direction direction);
        
        bool selectorOn;
        int currentButton;
        int maxButton;
        std::vector<Vec2> positions;
        Selector* selector;
};

#endif