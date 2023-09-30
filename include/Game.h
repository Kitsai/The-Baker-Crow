#ifndef Game_h_
#define Game_h_

#include "SDL2/SDL.h"
#include <string>
#include <stack>
#include <State.h>
#include <Resources.h>

/// @brief Game it is the object that holds and runs all the game aspects.
class Game {
    public:
        Game(const char* title, int width, int height);
        Game(const Game&) = delete;
        Game(Game&&) = default;
        ~Game();

        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();

        void Push(State* state);

        void Run();

        float GetDeltaTime();

        int GetWindowWidth();
        int GetWindowHeight();
        
    private:
        void CalculateDeltaTime();

        int frameStart;
        float dt;

        static Game* instance;

        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::stack<std::unique_ptr<State>> stateStack;

        int windowWidth;
        int windowHeight;
};

#endif