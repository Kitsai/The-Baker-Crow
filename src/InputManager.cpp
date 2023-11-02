#include "InputManager.h"


InputManager::InputManager() {
    for(int i=0;i<6;i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }

    for(int i=0;i<416;i++) {
        keyState[i] = false;
        keyUpdate[i] = 0;
    }

    quitRequested = false;

    updateCounter = 0;

    mouseX = 0;
    mouseY = 0;

}

InputManager& InputManager::GetInstance() {
    static InputManager manager;
    return manager;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::KeyPress(int key) {
    if(key > 0x40000000) key -= 0x3FFFFF81;
    return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key) {
    if(key > 0x40000000) key -= 0x3FFFFF81;
    return !(mouseState[key]) && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    if(key > 0x40000000) key -= 0x3FFFFF81;
    return keyState[key];
}

bool InputManager::AnyKeyDown() {
    for(int i=0;i<416;i++) if(keyState[i]) return true;
    return false;
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && mouseUpdate[button] == updateCounter;    
}

bool InputManager::MouseRelease(int button) {
    return !(mouseState[button]) && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

bool InputManager::AnyMouseDown() {
    for(int i=0;i<6;i++) if(mouseState[i]) return true;
    return false;
}

void InputManager::Update() {
    SDL_Event event;

    /// coordenadas do mouse;
    SDL_GetMouseState(&mouseX,&mouseY);


    quitRequested = false;

    updateCounter++;

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
            quitRequested = true;
        
        /// Seta o status do botao apertado como true no vetor
        if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            mouseState[event.button.button] = event.type == SDL_MOUSEBUTTONDOWN;
            mouseUpdate[event.button.button] = updateCounter;
        }

        /// Calcula o indice caso seja necessario e seta como verdadeiro ou falso baseado no evento ocorrido
        if((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat != 1) {
            int id = event.key.keysym.sym; 
            id -= (id >= 0x40000000)? 0x3FFFFF81 : 0;
            keyState[id] = event.type == SDL_KEYDOWN;
            keyUpdate[id] = updateCounter;
        }

    }            
}