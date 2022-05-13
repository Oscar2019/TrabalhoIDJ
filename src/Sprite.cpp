#include "Sprite.h"
#include "Game.h"
#include "Error.h"
#include "GameObject.h"
#include "Resources.h"
#include <cstring>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER 
// #define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"
#include <iostream>

const std::string Sprite::TYPE = "Sprite";

// construtor default
Sprite::Sprite(GameObject& associated) : 
  Component(associated), 
  texture(nullptr), 
  width(0), 
  height(0), 
  clipRect{},
  scale(1, 1),
  frameCount(1),
  currentFrame(),
  timeElapsed(),
  frameTime(1),
  secondsToSelfDestruct(0),
  selfDestructCount(){
}

// construtor que abre um sprite
Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct) : 
  Component(associated), 
  texture(nullptr), 
  width(0), 
  height(0), 
  clipRect{},
  scale(1, 1),
  frameCount(frameCount),
  currentFrame(),
  timeElapsed(),
  frameTime(frameTime),
  secondsToSelfDestruct(secondsToSelfDestruct),
  selfDestructCount(){
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

    if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height) < 0){ // Obtem a largura e a altura
        throw EngineRuntimeError_Line("[Sprite][Open(file)]SDL_QueryTexture: " + std::string(SDL_GetError()) + "\n");
    }
    width /= frameCount;

    // SetClip(0, 0, width / frameCount, height); // Seta o tamanho
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
    // SDL_Rect rectDest{x, y, int(w * scale.x / frameCount), int(h * scale.y)}; // Cria o rect de restino
    SDL_Rect rectDest{x, y, int(w * scale.x), int(h * scale.y)}; // Cria o rect de restino
    
    if(SDL_RenderCopyEx(renderer, texture.get(), &clipRect, &rectDest, associated.angleDeg, nullptr, SDL_FLIP_NONE) < 0){
        throw EngineRuntimeError_Line("[Sprite][Render(x, y, w, h)]SDL_QueryTexture: " + std::string(SDL_GetError()) + "\n");
    }
}

// Renderiza o Sprite
void Sprite::Render(int x, int y){
    // Render(x, y, width / frameCount, height);
    Render(x, y, width, height);
}

// retorna largura
int Sprite::getWidth(){
    // return width;
    // return (int) (width * scale.x / frameCount);
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
    if(secondsToSelfDestruct > 0){
        selfDestructCount.update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct){
            associated.RequestDelete();
        }
    }
    timeElapsed += dt;
    if(timeElapsed >= frameTime){
        SetFrame((currentFrame + 1) % frameCount);
        timeElapsed = 0;
    }
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

void Sprite::SetFrame(int frame){
    if(currentFrame != frame){
        currentFrame = frame;
        SetClip(currentFrame * width, clipRect.y, clipRect.w, clipRect.h);
    }
}

void Sprite::SetFrameCount(int frameCount){
    frameCount = frameCount;
    SetFrame(0);
}

void Sprite::SetFrameTime(float frameTime){
    frameTime = frameTime;
}
