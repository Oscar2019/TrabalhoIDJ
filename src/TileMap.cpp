#include "TileMap.h"
#include "State.h"
#include "Game.h"
#include <fstream>
#include <string>
#include <iostream>


TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated), tileMatrix(), tileSet(tileSet), mapWidth(0), mapHeight(0), mapDepth(0){
    Load(file);
}

TileMap::~TileMap(){
    
}

void TileMap::Load(std::string file){
    std::fstream f_file(file, std::fstream::in);
    std::string str_tmp;
    
    std::getline(f_file, str_tmp, ','); // Lê largura
    mapWidth = std::stoi(str_tmp);

    std::getline(f_file, str_tmp, ','); // Lê altura
    mapHeight = std::stoi(str_tmp);
    
    std::getline(f_file, str_tmp, ','); // Lê profundidade
    mapDepth = std::stoi(str_tmp);
    
    // static int aux = 0;

    tileMatrix.reserve(mapWidth * mapHeight * mapDepth);
    for(int i = 0; i < mapDepth; i++){
        for(int j = 0; j < mapHeight; j++){
            for(int k = 0; k < mapWidth; k++){
                std::getline(f_file, str_tmp, ','); // Lê tile
                int tile = std::stoi(str_tmp);
                tile--;
                // if(i * mapHeight * mapWidth + j * mapWidth + k == tileMatrix.size()){
                //     aux++;
                // }
                tileMatrix.push_back(tile);   
                // At(k, j, i) = tile;
            }
        }
    }
    // std::cout << aux << "\n";
}

void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
    return tileMatrix.at(z * mapHeight * mapWidth + y * mapWidth + x);
}

void TileMap::Render(){
    for(int i = 0; i < mapDepth; i++){
        RenderLayer(i, associated.box.x, associated.box.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            tileSet->RenderTile(At(j, i, layer), j * tileSet->GetTileWidth() + cameraX, i * tileSet->GetTileHeight() + cameraY);   
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