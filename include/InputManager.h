#ifndef InputManager_h_
#define InputManager_h_

#include "defines/DefineInput.h"
#include "SDL2/SDL.h"

/// @brief A manager that handles an input events
class InputManager {
    private:
        /// @brief Array that saves the state of mouse buttons.
        bool mouseState[6];
        /// @brief Array that saves the last frame the mouse button was pressed.
        int mouseUpdate[6];
        /// @brief Flag that tells whether a mouse button is pressed.
        bool mouseDown;

        /// @brief Array that saves the state of keyboard keys.
        bool keyState[416];
        /// @brief Array that saves the last frame the key was pressed.
        int keyUpdate[416];
        /// @brief Flag that tells whether a key is pressed.
        bool keyDown;

        /// @brief flag that saves whether the game should end.
        bool quitRequested;

        /// @brief A counter for how many times Update was run.
        int updateCounter;

        /// @brief x coordinate for the mouse cursor.
        int mouseX;
        /// @brief y coordinate for the mouse cursor.
        int mouseY;

        /// @brief Initializes all vectors with the defoult values of false and 0. And all other members following the same pattern.
        InputManager();
        //~InputManager();

    public:
        /// @brief 
        /// Gets the instance of Input manager.
        /// @return 
        /// A reference to the Input Manager instance.
        static InputManager& GetInstance();

        /// @brief Getter for quitRequested.
        /// @return true if a quit was requested on InputManager::Update().
        bool QuitRequested();

        /// @brief Getter for mouseX.
        /// @return int that corresponds to mouse position on the x axis.
        int GetMouseX();
        /// @brief Getter for mouseY.
        /// @return int that corresponds to mouse position on the y axis.
        int GetMouseY();

        /// @brief Checks if a key was pressed this frame. 
        /// @param key The key that should be checked. 
        /// @return true if the the key is pressed and was pressed this frame. 
        bool KeyPress(int key);
        /// @brief Checks if a key was released this frame. 
        /// @param key The key that should be checked. 
        /// @return true if the the key is released and was released this frame. 
        bool KeyRelease(int key);
        /// @brief Checks if a key is pressed. 
        /// @param key The key that should be checked. 
        /// @return true if the the key is pressed. 
        bool IsKeyDown(int key);
        /// @brief Checks if any key is pressed at the moment.
        /// @return true if any key is being pressed.
        bool AnyKeyDown();

        /// @brief Checks if a mouse button was pressed this frame.
        /// @param button The button that should be checked.
        /// @return true if the the button is pressed and was pressed this frame.
        bool MousePress(int button);
        /// @brief Checks if a mouse button was released this frame.
        /// @param button The button that should be checked.
        /// @return true if the the button is released and was released this frame.
        bool MouseRelease(int button);
        /// @brief Checks if a mouse button is pressed.
        /// @param button The button that should be checked.
        /// @return true if the the button is pressed.
        bool IsMouseDown(int button);
        /// @brief 
        /// @return 
        bool AnyMouseDown();

        /// @brief 
        /// Gets current mouse position. Resets quit Requested. Updates the update counter.
        /// After that, while there is is an event to be polled using SDL_PollEvent() checks what is the event type and if it was a quit updates the quit requested member.
        /// If it if a button or key press or release updates the arrays with the change and updates when it was updated.
        void Update();
};

#endif