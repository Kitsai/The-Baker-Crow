#ifndef Controller_h_
#define Controller_h_

#include "SDL2/SDL.h"

#include "defines/DefineInput.h"

class Controller {
    public:
        static Controller* CheckControllers();
        Controller(int id);
        ~Controller();

        int GetAxis(short axis);

        bool ButtonPress(int button);
        bool ButtonRelease(int button);
        bool IsButtonDown(int button);

        void Update();
        int GetId();
        bool IsActive();

        void ProcessEvent(SDL_Event& event);

    private:
        bool buttonState[22];
        int buttonUpdate[22];

        int axisPositions[7];
        
        int id; 
        bool active;

        unsigned updateCounter;

        SDL_GameController* controller;
        
};

#endif