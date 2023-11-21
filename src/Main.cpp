#include "Game.h"
#include "OverworldState.h"
#include "PuzzleState.h"

int main(int argc, char** argv) {
    
    Game& game = Game::GetInstance();
    game.Push(new PuzzleState(3));
    game.Run();
    
    return 0;
}