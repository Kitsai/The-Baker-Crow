#ifndef InputManager_h_
#define InputManager_h_

#include <defines/DefineInput.h>
#include "SDL2/SDL.h"

/// @brief A manager that handles an input events
class InputManager {
    private:
        bool mouseState[6];
        int mouseUpdate[6];

        bool keyState[416];
        int keyUpdate[416];

        bool quitRequested;

        int updateCounter;

        int mouseX;
        int mouseY;

        InputManager();
        //~InputManager();

    public:
        static InputManager& GetInstance();

        bool QuitRequested();

        int GetMouseX();
        int GetMouseY();

        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);

        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);

        void Update();
};

#endif