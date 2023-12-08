#ifndef Sprite_h_
#define Sprite_h_

#include "SDL2/SDL_image.h"
#include "Rect.h"
#include <string>
#include "GameObject.h"

/// @brief An image component.
class Sprite: public Component {
    private:
        /// @brief shared pointer to the texture that the sprite has.
        std::shared_ptr<SDL_Texture> texture;

        /// @brief width of the opened image. 
        int width;
        /// @brief height of the opened image.
        int height;
        /// @brief rect that is used to render the sprite.
        SDL_Rect clipRect;

        /// @brief number of frames of image.
        int frameCount;
        /// @brief current frame being  displayed.
        int currentFrame;
        /// @brief time passed since component started.
        float timeElapsed;
        /// @brief interval between frames.
        float frameTime;

        /// @brief Vector containing the scale of the sprite.
        Vec2 scale;

        /// @brief A Timer that checks when game object should be deleted.
        Timer selfDestructCount;
        /// @brief time to object be destroyed.
        float secondsToSelfDestruct;

        SDL_RendererFlip flip;
        Uint8 alpha;
    public:
        /// @brief Constructor for Sprite component. Starts all members.
        /// @param assoc Object the component is part off.
        /// @param frameCount Number of frames the image has. Default = 1 that is the image is not a animation.
        /// @param frameTime Time per frame. Default = 0 since if not an animation there is no time between frames.
        /// @param secondsToSelfDestruct Seconds until sprite should delete the associated object.
        Sprite(GameObject& assoc, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
        /// @brief Constructor for Sprite component. Starts all members.
        /// @param assoc Object the component is part off.
        /// @param file relative path to the file that should be opened.
        /// @param frameCount Number of frames the image has. Default = 1 that is the image is not a animation.
        /// @param frameTime Time per frame. Default = 0 since if not an animation there is no time between frames.
        /// @param secondsToSelfDestruct Seconds until sprite should delete the associated object.
        Sprite(GameObject& assoc, std::string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
        ~Sprite();

        /// @brief Set the current frame.
        /// @param frame frame that should be put on.
        void SetFrame(int frame);
        /// @brief Change how many frames in the sprite.
        /// @param frame number of frames.
        void SetFrameCount(int frame);
        /// @brief Set the interval between frames.
        /// @param frameTime time in seconds to change from a frame to another.
        void SetFrameTime(float frameTime);

        /// @brief Opens the given file with the Resource Manager and gets its width and height.
        /// @param file relative path to image file.
        void Open(std::string file);
        /// @brief Sets the sprite clip with custom values.
        /// @param x Position on x axis.
        /// @param y Position on y axis.
        /// @param w Image width.
        /// @param h Image height.
        void SetClip(int x, int y, int w, int h);

        /// @brief Renders the image with the position on the asociated game object.
        void Render();
        /// @brief Renders the image with the full width and height and in a custom position.
        /// @param x Position on the x axis.
        /// @param y Position on the y axis.
        void Render(int x, int y);
        /// @brief Renders the image with custom positions and custom size.
        /// @param x Position on x axis.
        /// @param y Position on y axis.
        /// @param w Render width.
        /// @param h Render height.
        void Render(int x, int y, int w, int h);

        /// @brief Getter for width. Note: check whehter a image is open before using.
        /// @return int corresponding to image width.
        int GetWidth();
        /// @brief Getter for height. Note: check whehter a image is open before using.
        /// @return int corresponding to image height.
        int GetHeight();

        void SetAlpha(Uint8 alpha);
        void SetFlip(SDL_RendererFlip flip);
        /// @brief Sets the scale to the the given coordinates.
        /// @param scale Vector containing the scale for both axis.
        void SetScale(Vec2 scale);
        /// @brief Sets the scale to the the given coordinates.
        /// @param scaleX scale of the X axis.
        /// @param scaleY scale of the Y axis.
        void SetScale(float scaleX, float scaleY);
        /// @brief Getter for the Scale.
        /// @return A vector containing the current scale.
        Vec2 GetScale();

        /// @brief Checks if the imaage file has been opened.
        /// @return true if the file is already open.
        bool IsOpen(); 
        /// @brief Updates the component. If is an animation updates the current frame. And checks if the object should be destructed.
        /// @param dt Delta Time.
        void Update(float dt);  
        /// @brief Returns whether the object is of a certain type.
        /// @param type Type to be checked.
        /// @return True if type matches with the passed argument. 
        bool Is(std::string type);  

        void SetFocus(float scaleX, float scaleY);
        void UnSetFocus();
};

#endif