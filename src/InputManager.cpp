#include <InputManager.h>

/// @brief 
/// Gets the instance of Input manager.
/// @return 
/// A reference to the Input Manager instance.
InputManager& InputManager::GetInstance() {
    static InputManager manager;
    return manager;
}

/// @brief 
/// Initializes all vectors with the defoult values of false and 0. And all other members following the same pattern.
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

/// @brief 
/// Gets current mouse position. Resets quit Requested. Updates the update counter.
/// After that, while there is is an event to be polled using SDL_PollEvent() checks what is the event type and if it was a quit updates the quit requested member.
/// If it if a button or key press or release updates the arrays with the change and updates when it was updated.
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

/// @brief 
/// Checks if a mouse button was pressed this frame.
/// @param button 
/// The button that should be checked.
/// @return 
/// true if the the button is pressed and was pressed this frame.
bool InputManager::MousePress(int button) {
    return mouseState[button] && mouseUpdate[button] == updateCounter;    
}

/// @brief 
/// Checks if a mouse button was released this frame.
/// @param button 
/// The button that should be checked.
/// @return 
/// true if the the button is released and was released this frame.
bool InputManager::MouseRelease(int button) {
    return !(mouseState[button]) && mouseUpdate[button] == updateCounter;
}

/// @brief 
/// Checks if a mouse button is pressed.
/// @param button 
/// The button that should be checked.
/// @return 
/// true if the the button is pressed.
bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

/// @brief 
/// Checks if a key was pressed this frame.
/// @param key 
/// The key that should be checked.
/// @return 
/// true if the the key is pressed and was pressed this frame.
bool InputManager::KeyPress(int key) {
    if(key > 0x40000000) key -= 0x3FFFFF81;
    return keyState[key] && keyUpdate[key] == updateCounter;
}

/// @brief 
/// Checks if a key was released this frame.
/// @param key 
/// The key that should be checked.
/// @return 
/// true if the the key is released and was released this frame.
bool InputManager::KeyRelease(int key) {
    if(key > 0x40000000) key -= 0x3FFFFF81;
    return !(mouseState[key]) && keyUpdate[key] == updateCounter;
}

/// @brief 
/// Checks if a key is pressed.
/// @param key 
/// The key that should be checked.
/// @return 
/// true if the the key is pressed.
bool InputManager::IsKeyDown(int key) {
    if(key > 0x40000000) key -= 0x3FFFFF81;
    return keyState[key];
}

/// @brief 
/// Getter for mouseX.
/// @return 
/// int that corresponds to mouse position on the x axis.
int InputManager::GetMouseX() {
    return mouseX;
}

/// @brief 
/// Getter for mouseY.
/// @return 
/// int that corresponds to mouse position on the y axis.
int InputManager::GetMouseY() {
    return mouseY;
}

/// @brief 
/// Getter for quitRequested.
/// @return 
/// true if a quit was requested on InputManager::Update().
bool InputManager::QuitRequested() {
    return quitRequested;
}