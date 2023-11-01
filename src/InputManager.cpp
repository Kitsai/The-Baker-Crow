#include <InputManager.h>


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

    controller->Update();

    quitRequested = false;

    updateCounter++;

    while(SDL_PollEvent(&event)) {

        switch (event.type)
        {
        case SDL_QUIT:
            quitRequested = true;
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            mouseState[event.button.button] = true;
            mouseUpdate[event.button.button] = updateCounter;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseState[event.button.button] = false;
            mouseUpdate[event.button.button] = updateCounter;
            break;

        case SDL_KEYDOWN:
            if(event.key.repeat != 1) break;
            int id = event.key.keysym.sym;
            if(id >= 0x40000000) id -= 0x3FFFFF81;

            keyState[id] = true;
            keyUpdate[id] = updateCounter;
            break;

        case SDL_KEYUP:
            if(event.key.repeat != 1) break;
            int id = event.key.keysym.sym;
            if(id >= 0x40000000) id -= 0x3FFFFF81;

            keyState[id] = false;
            keyUpdate[id] = updateCounter;
            break;

        case SDL_CONTROLLERDEVICEADDED:
            if(!controller) controller = new Controller((int)event.cdevice.which);
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            if(controller && event.cdevice.which == controller->GetId()) {
                delete controller;
                controller = Controller::CheckControllers();
            }
            break;
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
            if(controller && event.cdevice.which == controller->GetId()) {
                controller->ProcessEvent(event);
            }
            break;

        default:
            break;
        }
    }            
}