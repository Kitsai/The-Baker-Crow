#include "Game.h"
#include "OverworldState.h"
#include "PuzzleState.h"

int main(int argc, char** argv) {
    
    Game& game = Game::GetInstance();
    game.Push(new PuzzleState(1));
    game.Run();
    
    return 0;
}