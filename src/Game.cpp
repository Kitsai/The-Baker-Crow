#include <Game.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_ttf.h"
#include <InputManager.h>
#include <iostream>

Game* Game::instance = nullptr;


Game::Game(const char* title, int width, int height) {
    if(Game::instance != nullptr) { 
        std::cerr << "A Game instance is already running" << std::endl;      
        exit(-1);    
    }
    Game::instance = this;
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK |SDL_INIT_GAMECONTROLLER) != 0) {
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

Game::~Game() {
    if(storedState!=nullptr) delete storedState;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_Quit();
}

Game& Game::GetInstance() {
    if(Game::instance == nullptr) 
        instance = new Game("The Baker Crow", 1280, 720);
    return *Game::instance;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetCurrentState() {
    return *stateStack.top();
}


void Game::Push(State* state) {
    storedState = state;
}


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

float Game::GetDeltaTime() {
    return dt;
}

int Game::GetWindowWidth() {
    return windowWidth;
}

int Game::GetWindowHeight() {
    return windowHeight;
}

void Game::CalculateDeltaTime() {
    unsigned t = SDL_GetTicks();
    dt = (float)(t-frameStart)*0.0001F;
    frameStart = t;
}