#include "Game.h"
#include "states/StartState.h"
#include "states/BakeryState.h"

int main(int argc, char** argv) {
    
    Game& game = Game::GetInstance();
    game.Push(new BakeryState());
    game.Run();
    
    return 0;
}
