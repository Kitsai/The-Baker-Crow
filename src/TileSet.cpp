#include <TileSet.h>

/// @brief Constructor for tile set.
/// @param associated Associated game object.
/// @param tileWidth Width of the tiles.
/// @param tileHeight height of the tiles.
/// @param file image corresponding to the tile set.
TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, const char* file) {
    this->tileHeight = tileHeight;
    this->tileWidth = tileWidth;
    tileSet = new Sprite(associated,file);
    if(tileSet->IsOpen()) {
        rows = tileSet->GetHeight()/tileHeight;
        columns = tileSet->GetWidth()/tileWidth;
    }
}

/// @brief Deletes the Sprite before deleting.
TileSet::~TileSet() {
    delete tileSet;
}

/// @brief Render individual tile at given coordinates.
/// @param index index of the tile on the tile set.
/// @param x Position on the x axis.
/// @param y Position on the y axis.
void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index < (unsigned)(rows*columns)) {
        tileSet->SetClip((index%columns)*tileWidth,(index/columns)*tileHeight,tileWidth,tileHeight);
        tileSet->Render(x,y,tileWidth,tileHeight);
    }
}

/// @brief Getter for tileWidth
/// @return the width of tiles
int TileSet::GetTileWidth() {
    return tileWidth;
}

/// @brief Getter for tileHeight
/// @return the height of tiles.
int TileSet::GetTileHeight() {
    return tileHeight;
}