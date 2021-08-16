#include "Sprite.h"
#include "Game.h"
#include "Error.h"
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Sprite::Sprite() : texture(nullptr), width(0), height(0), clipRect{}{
    
}

Sprite::Sprite(std::string file) : texture(nullptr), width(0), height(0), clipRect{}{
    Open(file);   
}

Sprite::~Sprite(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
    Game *game = Game::GetInstance();
    
    texture = IMG_LoadTexture(game->GetRenderer(), file.c_str());
    
    if(texture == nullptr){
        throw EngineRuntimeError_Line("[Sprite][Open(file)]IMG_LoadTexture: " + std::string(IMG_GetError()) + "\n");
    }

    if(SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) < 0){
        std::cerr << 1 << "\n";
        throw EngineRuntimeError_Line("[Sprite][Open(file)]SDL_QueryTexture: " + std::string(SDL_GetError()) + "\n");
    }

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y){
    Game *game = Game::GetInstance();
    SDL_Renderer *renderer = game->GetRenderer();
    SDL_Rect rectDest{0, 0, 1024, 600};
    if(SDL_RenderCopy(renderer, texture, &clipRect, &rectDest) < 0){
        throw EngineRuntimeError_Line("[Sprite][Render(x, y)]SDL_QueryTexture: " + std::string(SDL_GetError()) + "\n");
    }

}

int Sprite::getWidth(){
    return width;
}

int Sprite::getHeight(){
    return height;
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}
