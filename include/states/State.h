#ifndef State_h_
#define State_h_

#include <memory>
#include <vector>
#include "Sprite.h"
#include "GameObject.h"
#include "Music.h"
#include "Sound.h"
#include "TileMap.h"
#include "CameraFollower.h"
#include "Text.h"
#include "Collider.h"

/// @brief Abstract class for a state of the game.
class State {
    protected:
        Music* backGraundMusic;
        /// @brief flag that tells whether this state should be popped from the stack.
        bool popRequested;
        /// @brief flag that talls whether the game should be quitted.
        bool quitRequested;
        /// @brief flag that saves whether the State has been started.
        bool started;

        /// @brief A vector of Game object.
        std::vector<std::shared_ptr<GameObject>> objectArray;

        /// @brief Starts the object Array.
        void StartArray();
        /// @brief Updates the objecy Array.
        /// @param dt Delta Time
        virtual void UpdateArray(float dt);
        /// @brief Renders the object Array.
        virtual void RenderArray();

        virtual void CheckCollisions();

        virtual void DeleteObjects();

    public:
        /// @brief Construtor fot the State. Initializes all variables.
        State();
        /// @brief clear the object array.
        virtual ~State();

        /// @brief Load assets that are used in this State.
        virtual void LoadAssets() = 0;
        /// @brief Updates the State.
        /// @param dt Delta Time.
        virtual void Update(float dt) = 0;
        /// @brief Render the State.
        virtual void Render() = 0;

        /// @brief Starts the State.
        virtual void Start() = 0;
        /// @brief Pause the State.
        virtual void Pause() = 0;
        /// @brief Resume the State.
        virtual void Resume() = 0;

        /// @brief Adds an object to the object vector.
        /// @param go Raw pointer to the object that should be added.
        /// @return  A weak pointer to the added object.
        virtual std::weak_ptr<GameObject> AddObject(GameObject* go);
        /// @brief Gets an object on the object vector.
        /// @param go Raw pointer to the object that should be searched.
        /// @return  A weak pointer to the searched object.
        virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

        /// @brief Getter for the popRequested flag.
        /// @return true if state should be popped.
        bool PopRequested();
        /// @brief Getter for the quitRequested flag.
        /// @return true if game should be ended.
        bool QuitRequested();
};

#endif