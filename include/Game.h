#ifndef Game_h_
#define Game_h_

#include "SDL2/SDL.h"
#include <string>
#include <stack>
#include "State.h"
#include "Resources.h"

/// @brief Game it is the object that holds and runs all the game aspects.
class Game {
    public:
        //deletes the copy constructor. And sets the move constructor as default.
        Game(const Game&) = delete;
        Game(Game&&) = default;

        /// @brief Finished all SDL libraries before destructing.
        ~Game();

        /// @brief Getter for the Game current instance. If the instance does not exist it is created.
        /// @return returns a reference to the current Game instance.
        static Game& GetInstance();
        /// @brief Getter for the Game Renderer.
        /// @return returns the current Renderer pointer to be used in the game.
        SDL_Renderer* GetRenderer();
        /// @brief Getter for the the state currently running.
        /// @return return a reference to the state on top of the state stack.
        State& GetCurrentState();

        /// @brief Pushes a new State into the state stack. 
        /// @param state Pointer to the State that need to be put on the stack.
        void Push(State* state);

        /// @brief Runs the Game. Starting by
        /// Getting the fist state. and starts the game loop. Where it deals with the state stack and updated and renders the current state. 
        /// Updates the Input Manager and calculated the Delta Time.
        void Run();

        /// @brief Getter for the delta time.
        /// @return return a float corresponding to the time passed between frames.
        float GetDeltaTime();
        /// @brief Getter for the current window Width.
        /// @return int corresponding to the game window width
        int GetWindowWidth();
        /// @brief Getter for the current window Height.
        /// @return int corresponding to the game window height.
        int GetWindowHeight();
        
    private:
        /// @brief Constructor for the Game Instance. Private so only the GetInstance() can create a new instance.
        /// @param title String that is going to be shown on top of the window.
        /// @param width Window width.
        /// @param height Window height.
        Game(const char* title, int width, int height);

        /// @brief Calculates the time passes since last frame.
        void CalculateDeltaTime();

        //////////////////////////////////////////////////////////

        /// @brief How many ticks has passed at the start of last frame.
        unsigned frameStart;

        /// @brief Time passes since last frame.
        float dt;

        /// @brief Current Game instance.
        static Game* instance;


        /// @brief Pointer to a State that has yet to be put on the stack.
        State* storedState;
        /// @brief Pointer to the game window.
        SDL_Window* window;
        /// @brief Pointer to the Game renderer.
        SDL_Renderer* renderer;
        /// @brief A stack that stores all the states currently on the game.
        std::stack<std::unique_ptr<State>> stateStack;

        int windowWidth;
        int windowHeight;
};

#endif