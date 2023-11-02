#ifndef TileSet_h_
#define TileSet_h_

#include "Sprite.h"
#include "GameObject.h"

#include <string>
#include <fstream>

/// @brief A tile set that contains a image that can be separated into different tiles.
class TileSet {
    public:
        /// @brief Constructor for tile set.
        /// @param associated Associated game object.
        /// @param tileWidth Width of the tiles.
        /// @param tileHeight height of the tiles.
        /// @param file image corresponding to the tile set.
        TileSet(GameObject& associated, int tileWidth,int tileHeight,std::string file);

        TileSet(GameObject& associated, int tileWidth,int tileHeight, std::string imgFile, std::string dataFile);
        /// @brief Deletes the Sprite before deleting.
        ~TileSet();

        /// @brief Render individual tile at given coordinates.
        /// @param index index of the tile on the tile set.
        /// @param x Position on the x axis.
        /// @param y Position on the y axis.
        void RenderTile(unsigned index,float x, float y);

        /// @brief Getter for tileWidth
        /// @return the width of tiles
        int GetTileWidth();
        /// @brief Getter for tileHeight
        /// @return the height of tiles.
        int GetTileHeight();
    private:
        /// @brief associated sprite.
        Sprite* tileSet;

        /// @brief number of tiles of rows.
        int rows;
        /// @brief number of tile columns.
        int columns;


        void OpenMetadata(std::string file);
        std::vector<unsigned> metadata;

        /// @brief width of each tile.
        int tileWidth;
        /// @brief height of each tile.
        int tileHeight;

};

#endif