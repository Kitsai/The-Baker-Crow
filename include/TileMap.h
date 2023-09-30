#ifndef TileMap_h_
#define TileMap_h_

#include <TileSet.h>
#include <GameObject.h>

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


/// @brief A tile map obejct that takes a tile set and renders its tiles following a given map.
class TileMap: public Component {
    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;

    public:
        TileMap(GameObject& associated, const char* file, TileSet* tileSet);

        void Load(const char* file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, float cameraX = 0, float cameraY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();

        void Update(float dt);
        bool Is(std::string type);
};

#endif