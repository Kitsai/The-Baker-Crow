#ifndef PuzzleState_h_
#define PuzzleState_h_

#include "Game.h"
#include "State.h"
#include "FoodItem.h"
#include "FoodPiece.h"
#include "FoodPuzzle.h"
#include "selectors/PuzzleSelector.h"

class PuzzleState: public State {
    private:
        FoodPuzzle* puzzle;
        void LoadMap();
        void CreatePuzzleSelector();
        void CreatePiece();
    public:
        PuzzleState(int puzzleNumber);
        ~PuzzleState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

};

#endif