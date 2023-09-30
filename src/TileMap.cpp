#include <TileMap.h>
#include <Camera.h>

/// @brief Constructor for Tile Map.
/// @param associated associated Game Object
/// @param file file to opened with map.
/// @param tileSet associated tile set/
TileMap::TileMap(GameObject& associated, const char* file, TileSet* tileSet): Component(associated) {
    Load(file);
    this->tileSet = tileSet;
}

/// @brief loads the values from map file that separates values by commas.
/// @param file Path to map file.
void TileMap::Load(const char* file) {
    std::ifstream myfile (file);
    char auxc;
    if(myfile.is_open()) {
        myfile >> mapWidth >> auxc >> mapHeight >> auxc >> mapDepth >> auxc;
        while(myfile) {
            int aux; myfile >> aux >> auxc;
            tileMatrix.push_back(aux-1);
        }
    }
}

/// @brief Sets the tile set to passed argument.
/// @param tileSet tile set to be associated.
void TileMap::SetTileSet(TileSet* tileSet) {
    delete this->tileSet;
    this->tileSet = tileSet;
} 

/// @brief Gets value on the position of 3d map.
/// @param x Position on x axis.
/// @param y Position on y axis.
/// @param z Position on z axis.
/// @return Value at passed coordinates.
int& TileMap::At(int x, int y, int z) {
    int at = 0;
    at += y*mapWidth;
    at += x;
    at += z*mapWidth*mapHeight; 
    return tileMatrix[at];
}

/// @brief Render Layer based on map size.
/// @param layer Current layer being rendered.
/// @param cameraX position x of the camera.
/// @param cameraY position y of the camera.
void TileMap::RenderLayer(int layer,float cameraX,float cameraY) {
    for(unsigned i = 0; i < mapHeight*mapWidth; i++) {
        tileSet->RenderTile(tileMatrix[i + layer*mapHeight*mapWidth],(i%mapWidth)*tileSet->GetTileWidth() - cameraX,(i/mapWidth)*tileSet->GetTileHeight() - cameraY);
    }
}

/// @brief Render all map layers.
void TileMap::Render() {
    for(int i = 0; i < mapDepth; i++) {
        RenderLayer(i,Camera::pos.x,Camera::pos.y);
    }
}

/// @brief Getter for mapWidth
/// @return the width of the map.
int TileMap::GetWidth() {
    return mapWidth;
}

/// @brief Getter for mapHeight
/// @return the height of the map.
int TileMap::GetHeight() {
    return mapHeight;
}

/// @brief Getter for mapDepth
/// @return the depth of the map.
int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(float dt) {

}

/// @brief 
/// Returns whether the object is of a certain type.
/// @param type 
/// Type to be checked.
/// @return 
/// True if type matches with the passed argument.
bool TileMap::Is(std::string type) {
    if(type == "TileMap") 
        return true;
    else
        return false; 
}