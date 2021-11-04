#include "State.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Face.h"
#include "Game.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Game.h"
#include "Sound.h"
#include "CameraFollower.h"
#include <iostream>

// Construtor default
State::State() : 
  camera(),
  objectArray(), 
  goTileMap(nullptr),
  music(), 
  quitRequested(false), 
  tileSet(nullptr){

}


State::~State(){
    if(tileSet != nullptr){
        delete tileSet;
    }
    objectArray.clear();
}

// retorna o valor da requisição de saída
bool State::QuitRequested(){
    return quitRequested;
}

// carrega os assts
void State::LoadAssets(){

    GameObject *go = nullptr;
    
    go = new GameObject();
    Sprite *bg = new Sprite(*go, "assets/img/ocean.jpg");
    CameraFollower *cf = new CameraFollower(*go);
    go->box.x = 0;
    go->box.y = 0;
    go->box.w = bg->getWidth();
    go->box.h = bg->getHeight();
    go->AddComponent(bg);
    go->AddComponent(cf);
    objectArray.emplace_back(go);
    
    // Game *game = Game::GetInstance();
    goTileMap = new GameObject();
    goTileMap->box.x = 0;
    goTileMap->box.y = 0;
    goTileMap->box.w = bg->getWidth();
    goTileMap->box.h = bg->getHeight();
    tileSet = new TileSet(*goTileMap, 64, 64, "assets/img/tileset.png");
    TileMap *tileMap = new TileMap(*goTileMap, "assets/map/tileMap.txt", tileSet);
    
    goTileMap->AddComponent(tileMap);
    objectArray.emplace_back(goTileMap);

	
    music.Open("assets/audio/stageState.ogg");
    music.Play();
}

// atualiza o estado
void State::Update(float dt){
    quitRequested = InputManager::GetInstance().QuitRequested();
    Input();
    auto end = objectArray.end();
    camera.Update(dt);
    
    for(auto it = objectArray.begin(); it != end; it++){
        auto &go = *it;
        go->Update(dt);
    }
    for(auto it = objectArray.begin(); it != end; ){
        auto &go = *it;
        if(go->IsDead()){
            it = objectArray.erase(it);
            end = objectArray.end();
        } else{
            it++;
        }
    }
}

// renderiza o estado
void State::Render(){
    // goTileMap->box.x = camera.pos.x;
    // goTileMap->box.y = camera.pos.y;
    auto end = objectArray.end();
    for(auto it = objectArray.begin(); it != end; it++){
        auto &go = *it;
        go->box.x -= camera.pos.x;
        go->box.y -= camera.pos.y;
        go->Render();
        go->box.x += camera.pos.x;
        go->box.y += camera.pos.y;
    }
}


void State::Input(){
    InputManager &input = InputManager::GetInstance();
    quitRequested = input.QuitRequested() || input.KeyPress(ESCAPE_KEY);
	int mouseX = input.GetMouseX();
    int mouseY = input.GetMouseY();
    mouseX += camera.pos.x;
    mouseY += camera.pos.y;

    if(input.KeyPress(SPACE_KEY)){
        Vec2 objPos = Vec2::rotate(Vec2( 200, 0 ), -PI + PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
        AddObject((int)objPos.x, (int)objPos.y);
    }
    if(input.IsMouseDown(LEFT_MOUSE_BUTTON)){ 
        for(auto it = objectArray.rbegin(); it != objectArray.rend(); it++){
            if(Rect::is_inside((*it)->box, {(float)mouseX, (float)mouseY} ) ) {
                Face *face = dynamic_cast<Face*>((*it)->GetComponent(Face::TYPE));
                if(face != nullptr){
                    face->Damage(std::rand() % 10 + 10);
                    break;
                }
            }
        } 
    }
    if(input.IsKeyDown(SDLK_LEFT)){
        camera.pos.x += 10;
    }
    if(input.IsKeyDown(SDLK_RIGHT)){
        camera.pos.x -= 10;
    }
    if(input.IsKeyDown(SDLK_UP)){
        camera.pos.y += 10;
    }
    if(input.IsKeyDown(SDLK_DOWN)){
        camera.pos.y -= 10;
    }

}

void State::AddObject(int mouseX, int mouseY){
    GameObject *go = new GameObject();
    Sprite *sprite = new Sprite(*go,"assets/img/penguinface.png");
    Sound *sound = new Sound(*go,"assets/audio/boom.wav");
    // Sound *sound = new Sound(*go,"assets/a/udio/stageState.ogg");
    Face *face = new Face(*go);
    go->box.x = mouseX;
    go->box.y = mouseY;
    go->box.w = sprite->getWidth();
    go->box.h = sprite->getHeight();
    go->AddComponent(sprite);
    go->AddComponent(sound);
    go->AddComponent(face);
    objectArray.emplace_back(go);
}

