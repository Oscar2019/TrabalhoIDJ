#include "Sprite.h"
#include "Game.h"
#include "Error.h"
#include "GameObject.h"
#include "Resources.h"
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const std::string Sprite::TYPE = "Sprite";

// construtor default
Sprite::Sprite(GameObject& associated) : 
  Component(associated), 
  texture(nullptr), 
  width(0), 
  height(0), 
  clipRect{},
  scale(1, 1){
}

// construtor que abre um sprite
Sprite::Sprite(GameObject& associated, std::string file) : 
  Component(associated), 
  texture(nullptr), 
  width(0), 
  height(0), 
  clipRect{},
  scale(1, 1){
    Open(file);  
}

// destrutor
Sprite::~Sprite(){
}
// Abre um sprite
void Sprite::Open(std::string file){
    // std::cout << file << "\n";
    auto resources = Resources::GetInstance();
    
    texture = resources.GetImage(file);
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
void Sprite::Render(int x, int y, int w, int h){
    Game *game = Game::GetInstance(); // Pega uma game
    SDL_Renderer *renderer = game->GetRenderer(); // Pega o renderer
    // SDL_Rect rectDest{x, y, int(w * scale.x), int(h * scale.y)}; // Cria o rect de restino
    // std:: cout  << int(w * scale.x) << " ";
    // std:: cout  << int(h * scale.y) << "\n";
    SDL_Rect rectDest{x, y, int(w * scale.x), int(h * scale.y)}; // Cria o rect de restino
    
    if(SDL_RenderCopyEx(renderer, texture, &clipRect, &rectDest, associated.angleDeg, nullptr, SDL_FLIP_NONE) < 0){
        throw EngineRuntimeError_Line("[Sprite][Render(x, y, w, h)]SDL_QueryTexture: " + std::string(SDL_GetError()) + "\n");
    }
}

// Renderiza o Sprite
void Sprite::Render(int x, int y){
    Render(x, y, width, height);
}

// retorna largura
int Sprite::getWidth(){
    // return width;
    return (int) (width * scale.x);
}

// retorna altura
int Sprite::getHeight(){
    // return height;
    return (int) (height * scale.y);
}

// verifila se o sprite está aberto
bool Sprite::IsOpen(){
    return texture != nullptr;
}

void Sprite::Update(float dt){

}

void Sprite::Render(){
    Rect &box = associated.box;
    Render(box.x, box.y, box.w, box.h);
}

bool Sprite::Is(std::string type){
    return type == Sprite::TYPE;
}


void Sprite::SetScaleX(float scaleX, float scaleY){
    scale.x = scaleX;
    scale.y = scaleY;
}

Vec2 Sprite::GetScaleY(){
    return scale;
}
