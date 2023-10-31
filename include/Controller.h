#ifndef Controller_h_
#define Controller_h_

#include "SDL2/SDL.h"

class Controller {
    public:
        static void CheckControllers();
        ~Controller();

    private:
        Controller();

        SDL_GameController* controller;
        
};

#endif