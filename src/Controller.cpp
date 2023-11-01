#include <Controller.h>

Controller* Controller::CheckControllers() {
    for(int i=0;i<SDL_NumJoysticks();i++) {
        if(SDL_IsGameController(i)) {
            return new Controller(i);
        }
    }
    return nullptr;
}

Controller::Controller(int id) {
    controller = SDL_GameControllerOpen(id);

    for(int i=0;i<22;i++) {
        buttonState[i] = false;
        buttonUpdate[i] = 0;
    }

    this->id = id;
    active = false;

    updateCounter = 0;
}

Controller::~Controller() {
    SDL_GameControllerClose(controller);
}

int Controller::GetAxis(short axis) {
    return axisPositions[axis];
}

bool Controller::ButtonPress(int button) {
    return buttonState[button] && buttonUpdate[button] == updateCounter;
}

bool Controller::ButtonRelease(int button) {
    return !buttonState[button] && buttonUpdate[button] == updateCounter;
}

bool Controller::IsButtonDown(int button) {
    return buttonState[button];
}

void Controller::Update() {
    for(int i=0;i<7;i++) SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis)i);
    
    updateCounter++;
}

int Controller::GetId() {
    return id;
}

bool Controller::IsActive() {
    return active;
}

void Controller::ProcessEvent(SDL_Event& event) {
    switch (event.type)
    {
    case SDL_CONTROLLERBUTTONDOWN:
        buttonState[(int)event.cbutton.button] = true;
        buttonUpdate[(int)event.cbutton.button] = updateCounter;
        break;
    case SDL_CONTROLLERBUTTONUP:
        buttonState[(int)event.cbutton.button] = false;
        buttonUpdate[(int)event.cbutton.button] = updateCounter;
        break;

    default:
        break;
    }
}