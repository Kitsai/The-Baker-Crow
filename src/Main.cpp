#include "Game.h"
#include "states/MenuState.h"

int main(int argc, char** argv) {
    
    Game& game = Game::GetInstance();
    game.Push(new MenuState());
    game.Run();
    
    return 0;
}