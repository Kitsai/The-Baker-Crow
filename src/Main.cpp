#include "Game.h"
#include "OverworldState.h"

int main(int argc, char** argv) {
    
    Game& game = Game::GetInstance();
    game.Push(new OverworldState());
    game.Run();
    
    return 0;
}