#include "Sprite.h"
#include "Game.h"
#include "Error.h"
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// construtor default
Sprite::Sprite() : texture(nullptr), width(0), height(0), clipRect{}{
    
}

// construtor que abre um sprite
Sprite::Sprite(std::string file) : texture(nullptr), width(0), height(0), clipRect{}{
    Open(file);   
}

// destrutor
Sprite::~Sprite(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

// Abre um sprite
void Sprite::Open(std::string file){
    if(texture != nullptr){ // Se existe um sprite anteriormente, então o destri
        SDL_DestroyTexture(texture);
    }
    Game *game = Game::GetInstance(); // pega uma instância do game
    
    texture = IMG_LoadTexture(game->GetRenderer(), file.c_str()); // carrega a imagem
    
    if(texture == nullptr){ // Se ocorreu um erro Exception
        throw EngineRuntimeError_Line("[Sprite][Open(file)]IMG_LoadTexture: " + std::string(IMG_GetError()) + "\n");
    }

    if(SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) < 0){ // Obtem a largura e a altura
        std::cerr << 1 << "\n";
        throw EngineRuntimeError_Line("[Sprite][Open(file)]SDL_QueryTexture: " + std::string(SDL_GetError()) + "\n");
    }

    SetClip(0, 0, width, height); // Seta o tamanho
}

// seta o tamanho do sprite
void Sprite::SetClip(int x, int y, int w, int h){
    clipRect = {x, y, w, h}; 
}

// Renderiza o Sprite
void Sprite::Render(int x, int y){
    Game *game = Game::GetInstance(); // Pega uma game
    SDL_Renderer *renderer = game->GetRenderer(); // Pega o renderer
    SDL_Rect rectDest{0, 0, 1024, 600}; // Cria o rect de restino
    if(SDL_RenderCopy(renderer, texture, &clipRect, &rectDest) < 0){
        throw EngineRuntimeError_Line("[Sprite][Render(x, y)]SDL_QueryTexture: " + std::string(SDL_GetError()) + "\n");
    }

}

// retorna largura
int Sprite::getWidth(){
    return width;
}

// retorna altura
int Sprite::getHeight(){
    return height;
}

// verifila se o sprite está aberto
bool Sprite::IsOpen(){
    return texture != nullptr;
}
