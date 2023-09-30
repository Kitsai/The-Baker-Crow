#ifndef TileSet_h_
#define TileSet_h_

#include <Sprite.h>
#include <GameObject.h>

#include <string>

/// @brief A tile set that contains a image that can be separated into different tiles.
class TileSet {
    private:
        Sprite* tileSet;

        int rows;
        int columns;

        int tileWidth;
        int tileHeight;

    public:
        TileSet(GameObject& associated, int tileWidth,int tileHeight,const char* file);
        ~TileSet();

        void RenderTile(unsigned index,float x, float y);

        int GetTileWidth();
        int GetTileHeight();
};

#endif