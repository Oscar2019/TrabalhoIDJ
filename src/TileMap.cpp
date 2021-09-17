#include "TileMap.h"
#include <fstream>
#include <string>


TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated), tileMatrix(), tileSet(tileSet), mapWidth(0), mapHeight(0), mapDepth(0){
    Load(file);
}

TileMap::~TileMap(){
    
}

void TileMap::Load(std::string file){
    std::fstream f_file(file, std::fstream::in);
    std::string str_tmp;
    
    std::getline(f_file, str_tmp); // Lê largura
    mapWidth = std::stoi(str_tmp);

    std::getline(f_file, str_tmp, ','); // Lê altura
    mapHeight = std::stoi(str_tmp);
    
    std::getline(f_file, str_tmp, ','); // Lê profundidade
    mapDepth = std::stoi(str_tmp);

    tileMatrix.reserve(mapWidth * mapHeight * mapDepth);
    for(int i = 0; i < mapDepth; i++){
        for(int j = 0; j < mapHeight; j++){
            for(int k = 0; k < mapWidth; k++){
                std::getline(f_file, str_tmp, ','); // Lê tile
                int tile = std::stoi(str_tmp);
                tile--;
                tileMatrix.push_back(tile);   
            }
        }
    }
}

void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
    return tileMatrix.at(z * mapHeight * mapWidth + y * mapWidth + x);
}

void TileMap::Render(){
    for(int i = 0; i < mapDepth; i++){
        RenderLayer(i);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            tileSet->RenderTile(At(j, i, layer), i * tileSet->GetTileWidth(), j * tileSet->GetTileHeight());   
        }
    }
}

int TileMap::GetWidth(){
    return mapWidth;    
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;
}

void TileMap::Update(float dt){
    
}

bool TileMap::Is(std::string type){
    return false;
}