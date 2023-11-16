#include "Game.h"
#include "states/StartState.h"

int main(int argc, char** argv) {
    
    Game& game = Game::GetInstance();
    game.Push(new StartState());
    game.Run();
    
    return 0;
}