#include "TileSet.h"
#include <iostream>
#include <cstdlib>


TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file): tileSet(associated), tileWidth(tileWidth), tileHeight(tileHeight){
    tileSet.Open(file);
    rows = tileSet.getHeight();
    colums = tileSet.getWidth();
    
    numRowiles = (rows / tileHeight);
    numColTiles = (colums / tileWidth);
    numTiles = numRowiles * numColTiles;
}

void TileSet::RenderTile(unsigned index, float x, float y){
    if(index >= numTiles){
        return;
    }
    int indexRow = index / numColTiles;
    int indexCol = index % numColTiles;
    
    tileSet.SetClip(indexCol * tileHeight, indexRow * tileWidth, tileWidth, tileHeight);
    tileSet.Render(x, y, tileWidth, tileHeight);
}

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}