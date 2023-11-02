#include "TileMap.h"
#include "Camera.h"


TileMap::TileMap(GameObject& associated, const char* file, TileSet* tileSet): Component(associated) {
    Load(file);
    this->tileSet = std::unique_ptr<TileSet>(tileSet);
}

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

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = std::unique_ptr<TileSet>(tileSet);
} 

int& TileMap::At(int x, int y, int z) {
    int at = 0;
    at += y*mapWidth;
    at += x;
    at += z*mapWidth*mapHeight; 
    return tileMatrix[at];
}

void TileMap::Render() {
    for(int i = 0; i < mapDepth; i++) {
        RenderLayer(i,Camera::pos.x,Camera::pos.y);
    }
}

void TileMap::RenderLayer(int layer,float cameraX,float cameraY) {
    for(unsigned i = 0; i < mapHeight*mapWidth; i++) {
        tileSet->RenderTile(tileMatrix[i + layer*mapHeight*mapWidth],(i%mapWidth)*tileSet->GetTileWidth() - cameraX,((double)i/mapWidth)*tileSet->GetTileHeight() - cameraY);
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(float dt) {

}


bool TileMap::Is(std::string type) {
    if(type == "TileMap") 
        return true;
    else
        return false; 
}