#include <TileSet.h>

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, const char* file) {
    this->tileHeight = tileHeight;
    this->tileWidth = tileWidth;
    tileSet = new Sprite(associated,file);
    if(tileSet->IsOpen()) {
        rows = tileSet->GetHeight()/tileHeight;
        columns = tileSet->GetWidth()/tileWidth;
    }
}

TileSet::~TileSet() {
    delete tileSet;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index < (unsigned)(rows*columns)) {
        tileSet->SetClip((index%columns)*tileWidth,(index/columns)*tileHeight,tileWidth,tileHeight);
        tileSet->Render(x,y,tileWidth,tileHeight);
    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}