#include <Game.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_ttf.h"
#include <InputManager.h>
#include <iostream>

Game* Game::instance = nullptr;


/// @brief 
/// Follow the singletons aproach so if there is not an running instance of Game a new one is instanciated
/// @return 
/// returns the Game instance.
Game& Game::GetInstance() {
    if(Game::instance == nullptr) 
        instance = new Game("Lucas_Rocha_dos_Santos_211055325", 1024, 600);
    return *Game::instance;
}

/// @brief 
/// Game constructor which initializes the SDL Library and creates the game State.
/// @param title 
/// The title of the game window
/// @param width
/// The Width of the game window resolution 
/// @param height 
/// The Heght of the game window resolution
Game::Game(const char* title, int width, int height) {
    if(Game::instance != nullptr) { 
        std::cerr << "A Game instance is already running" << std::endl;      
        exit(-1);    
    }
    Game::instance = this;
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) != 0) {
        std::cerr << "Error Game:22 -  " << SDL_GetError() << std::endl;
        exit(-1);
    }

    int imageBitmask = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    if(imageBitmask == 0) {
        std::cerr << "Error Game:29 - " << SDL_GetError() << std::endl;
        exit(-1);
    }
    
    int mixerBitmask = Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG );
    if(mixerBitmask == 0) {
        std::cerr << "Error Game:36 - " << SDL_GetError() << std::endl;
        exit(-1);
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "Error Game:40 - " << SDL_GetError() << std::endl;
        exit(-1);
    }
    Mix_AllocateChannels(32);

    if(TTF_Init() != 0) {
        std::cerr << "Error - " << SDL_GetError() << std::endl;
        exit(-1);
    }

    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
    if(window == nullptr) {
        std::cerr << "Error Game:46 - " << SDL_GetError() << std::endl;
        exit(-1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        std::cerr << "Error Game:52 - " << SDL_GetError() << std::endl;
        exit(-1);
    }
    
    storedState = nullptr;

    frameStart = 0;
    dt = 0;

    windowWidth = width;
    windowHeight = height;
}

/// @brief 
/// Finished all the SDL library and deletes the State.
Game::~Game() {
    // if(storedState!=nullptr) delete storedState;

    // while(stateStack.size()) stateStack.pop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_Quit();
}

/// @brief 
/// Getter for the Game State
/// @return 
/// returns a reference to the current State
State& Game::GetCurrentState() {
    return *stateStack.top();
}


/// @brief 
/// Getter for the Game Renderer
/// @return 
/// Returns a pointer to the Renderer.
SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Push(State* state) {
    storedState = state;
}

/// @brief 
/// Loads the assets that are going to be used and plays the current music.
/// After that, starts the GameLoop in which it handles timing, Input, Updating the Game State
/// rendering the current Game State and presenting the current frame.
void Game::Run() {
    if(storedState == nullptr) return;
    stateStack.emplace(storedState);
    storedState = nullptr;
    GetCurrentState().Start();


    while(stateStack.size()) {
        CalculateDeltaTime();

        InputManager::GetInstance().Update();
        
        if(GetCurrentState().PopRequested()) {
            stateStack.pop();
            Resources::ClearImages();
            Resources::ClearMusics();
            Resources::ClearSounds();
            Resources::ClearFonts();
            
            if(stateStack.size()) GetCurrentState().Resume();
    }
        if(storedState != nullptr) {
            GetCurrentState().Pause();
            stateStack.emplace(storedState);
            storedState = nullptr;
            GetCurrentState().Start();
        }

        GetCurrentState().Update(dt);
        GetCurrentState().Render();

        SDL_RenderPresent(renderer);
        SDL_Delay(33);

        if(GetCurrentState().QuitRequested())
            while(stateStack.size()) stateStack.pop();
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();
}


/// @brief 
/// Calculate dt based on the past frame start and the ticks of the current frame
/// then multiplies it by 1000 to convert from miliseconds to seconds.
void Game::CalculateDeltaTime() {
    unsigned t = SDL_GetTicks();
    dt = (float)(t-frameStart)/1000.0F;
    frameStart = t;
}

/// @brief 
/// Getter for the dt(Delta Time)
/// @return 
/// returns a float that is the time between this and the last frame.
float Game::GetDeltaTime() {
    return dt;
}

int Game::GetWindowWidth() {
    return windowWidth;
}

int Game::GetWindowHeight() {
    return windowHeight;
}