#ifndef TileMap_h_
#define TileMap_h_

#include "TileSet.h"
#include "GameObject.h"

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


/// @brief A tile map obejct that takes a tile set and renders its tiles following a given map.
class TileMap: public Component {
    private:
        /// @brief Vector that hold the tile matrix.
        std::vector<int> tileMatrix;
        /// @brief Associated TileSet.
        std::unique_ptr<TileSet> tileSet;
        /// @brief Number of tiles on the x axis
        int mapWidth;
        /// @brief Number of tiles on the y axis
        int mapHeight;
        /// @brief Number layers.
        int mapDepth;

    public:
        /// @brief Constructor for Tile Map.
        /// @param associated associated Game Object
        /// @param file file to opened with map.
        /// @param tileSet associated tile set.
        TileMap(GameObject& associated, const char* file, TileSet* tileSet);

        /// @brief loads the values from map file that separates values by commas.
        /// @param file Path to map file.
        void Load(const char* file);
        /// @brief Sets the tile set to passed argument.
        /// @param tileSet tile set to be associated.
        void SetTileSet(TileSet* tileSet);
        /// @brief Gets value on the position of 3d map.
        /// @param x Position on x axis.
        /// @param y Position on y axis.
        /// @param z Position on z axis.
        /// @return Value at passed coordinates.
        int& At(int x, int y, int z = 0);
        /// @brief Render all map layers.
        void Render();
        /// @brief Render Layer based on map size.
        /// @param layer Current layer being rendered.
        /// @param cameraX position x of the camera.
        /// @param cameraY position y of the camera.
        void RenderLayer(int layer, float cameraX = 0, float cameraY = 0);
        /// @brief Getter for mapWidth
        /// @return the width of the map.
        int GetWidth();
        /// @brief Getter for mapHeight
        /// @return the height of the map.
        int GetHeight();
        /// @brief Getter for mapDepth
        /// @return the depth of the map.
        int GetDepth();

        /// @brief Updates the component.
        /// @param dt Delta Time.
        void Update(float dt);
        /// @brief Returns whether the object is of a certain type.
        /// @param type Type to be checked.
        /// @return True if type matches with the passed argument.
        bool Is(std::string type);
};

#endif