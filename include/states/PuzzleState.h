#ifndef PuzzleState_h_
#define PuzzleState_h_

#include "State.h"
#include "FoodPuzzle.h"

class PuzzleState: public State {
    private:
        FoodPuzzle* puzzle;
        void LoadMap();
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