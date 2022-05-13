#include "StageState.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Face.h"
#include "Game.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Game.h"
#include "Sound.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"
#include "PenguinCannon.h"
#include "Bullet.h"
#include "Bullet.h"
#include "EndState.h"
#include "GameData.h"
#include <iostream>


StageState::StageState() :
  State(),
  player(),
  camera(Camera::GetInstance(1)),
  tileSet(nullptr),
  backgroundMusic(), 
  goTileMap(nullptr),
  timer(){
    
}

StageState::~StageState(){
    if(tileSet != nullptr){
        delete tileSet;
    }
}

void StageState::LoadAssets(){
    
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
    // objectArray.emplace_back(go);
    AddObject(go);
    
    // Game *game = Game::GetInstance();
    goTileMap = new GameObject();
    goTileMap->box.x = 0;
    goTileMap->box.y = 0;
    goTileMap->box.w = bg->getWidth();
    goTileMap->box.h = bg->getHeight();
    tileSet = new TileSet(*goTileMap, 64, 64, "assets/img/tileset.png");
    TileMap *tileMap = new TileMap(*goTileMap, "assets/map/tileMap.txt", tileSet);
    
    goTileMap->AddComponent(tileMap);
    // objectArray.emplace_back(goTileMap);
    AddObject(goTileMap);

    go = new GameObject();
    Alien *alien = new Alien(*go, 6);
    go->AddComponent(alien);
    objectArray.emplace_back(go);
    // AddObject(go);
    
    go = new GameObject();
    PenguinBody *penguinBody = new PenguinBody(*go);
    go->box.x = 704;
    go->box.y = 640;
    go->AddComponent(penguinBody);
    // objectArray.emplace_back(go);
    camera.Follow(go);
    player = AddObject(go);





    // std::cout << "cheguei1\n";
	
    backgroundMusic.Open("assets/audio/stageState.ogg");
    backgroundMusic.Play();
}

void StageState::Update(float dt){
    InputManager& input = InputManager::GetInstance();
    quitRequested = input.QuitRequested();
    camera.Update(dt);
    
    for(int i = 0; i < objectArray.size(); i++){
        auto &go = objectArray[i];
        go->Update(dt);
    }
    std::vector<int> hasCollider; 
    for(int i = 0; i < objectArray.size(); i++){
        auto &go = objectArray[i];
        Collider *collider = dynamic_cast<Collider*>(go->GetComponent(Collider::TYPE));
        
        if(collider != nullptr){
            hasCollider.push_back(i);
        }
    }
    for(int i = 0; i < hasCollider.size(); i++){
        auto &go_a = objectArray[hasCollider[i]];
        Collider *collider_a = dynamic_cast<Collider*>(go_a->GetComponent(Collider::TYPE));
        for(int j = i + 1; j < hasCollider.size(); j++){
            auto &go_b = objectArray[hasCollider[j]];

            Collider *collider_b = dynamic_cast<Collider*>(go_b->GetComponent(Collider::TYPE));
            if(IsColliding(collider_a->box, collider_b->box, go_a->angleDeg, go_b->angleDeg)){
                go_a->NotifyCollision(*go_b.get());
                go_b->NotifyCollision(*go_a.get());
            }
        }
    }
    
    auto end = objectArray.end();
    for(auto it = objectArray.begin(); it != end; ){
        auto &go = *it;
        if(go->IsDead()){
            it = objectArray.erase(it);
            end = objectArray.end();
        } else{
            it++;
        }
    }
    
    if(player.expired()){
        timer.update(dt);
        if(timer.Get() >= 0.7){
            backgroundMusic.Stop();
            popRequested = true;
            gameData.playerVictory = false;
            Game::GetInstance()->Push(new EndState());
        }
    } else if(Alien::alienCount == 0){
        timer.update(dt);
        if(timer.Get() >= 0.56){
            backgroundMusic.Stop();
            popRequested = true;
            gameData.playerVictory = true;
            Game::GetInstance()->Push(new EndState());
        }
    }
}

void StageState::Render(){
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

void StageState::Start(){
    LoadAssets();
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Start();
    }
    
    started = true;
}

void StageState::Pause(){
    
}

void StageState::Resume(){
    
}
