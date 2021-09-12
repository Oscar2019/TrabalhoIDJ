#include "Sprite.h"
#include "Game.h"
#include "Error.h"
#include "GameObject.h"
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const std::string Sprite::TYPE = "Sprite";

// construtor default
Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr), width(0), height(0), clipRect{}{
    
}

// construtor que abre um sprite
Sprite::Sprite(GameObject& associated, std::string file) : Component(associated), texture(nullptr), width(0), height(0), clipRect{}{
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
    // SDL_Rect rectDest{500, 300, 500, 300}; // Cria o rect de restino

    SDL_Rect rectDest{0, 0, 1024, 600}; // Cria o rect de restino
    // associated.box.
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

void Sprite::Update(float dt){

}

void Sprite::Render(){
    Game *game = Game::GetInstance(); // Pega uma game
    SDL_Renderer *renderer = game->GetRenderer(); // Pega o renderer
    SDL_Rect rectDest{}; // Cria o rect de restino
    Rect &box = associated.box;
    rectDest.x = box.x;
    rectDest.y = box.y;
    rectDest.w = box.w;
    rectDest.h = box.h;
    if(SDL_RenderCopy(renderer, texture, &clipRect, &rectDest) < 0){
        throw EngineRuntimeError_Line("[Sprite][Render(x, y)]SDL_QueryTexture: " + std::string(SDL_GetError()) + "\n");
    }
}

bool Sprite::Is(std::string type){
    return type == Sprite::TYPE;
}