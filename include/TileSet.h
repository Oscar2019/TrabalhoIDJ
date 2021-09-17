#pragma once
#include <string>
#include "Sprite.h"
#include "GameObject.h"

class TileSet{
    public:
        TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file);
    
        void RenderTile(unsigned index, float x, float y);
    
        int GetTileWidth();
        int GetTileHeight();
    
    private:
        Sprite tileSet;

        int rows;
        int colums;

        int tileWidth;
        int tileHeight;

        int numRowiles;
        int numColTiles;
        int numTiles;
};