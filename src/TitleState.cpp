#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include "Text.h"
#include "Game.h"
#include "StageState.h"
#include <iostream>


TitleState::TitleState():
  State(),
  timer(){
    
}

TitleState::~TitleState(){
    
}

void TitleState::LoadAssets(){
    
    GameObject *go = nullptr;
    
    go = new GameObject();
    Sprite *bg = new Sprite(*go, "assets/img/title.jpg");
    // CameraFollower *cf = new CameraFollower(*go);
    go->box.x = 0;
    go->box.y = 0;
    go->box.w = bg->getWidth();
    go->box.h = bg->getHeight();
    // std::cout << bg->getWidth() << " ";
    // std::cout << bg->getHeight() << "\n";
    go->AddComponent(bg);
    // go->AddComponent(cf);
    AddObject(go);
    
    go = new GameObject();
    Text *text = new Text(*go, "assets/font/Call me maybe.ttf", 36, TextStyle::SOLID, "Precione SPACE para jogar", SDL_Color{50,80,20,255});
    go->box.x = 298;
    go->box.y = 510;
    go->AddComponent(text);
    AddObject(go);
}

void TitleState::Update(float dt){
    InputManager& input = InputManager::GetInstance();
    quitRequested = input.QuitRequested() || input.KeyRelease(ESCAPE_KEY);
    if(input.KeyPress(SPACE_KEY)){
        Game::GetInstance()->Push(new StageState());
    }
    timer.update(dt);
}

void TitleState::Render(){
    auto end = objectArray.end();
    for(auto it = objectArray.begin(); it != end; it++){
        auto &go = *it;
        // go->box.x -= camera.pos.x;
        // go->box.y -= camera.pos.y;
        if(go->GetComponent(Text::TYPE)){
            if(timer.Get() > 1){
                go->Render();
                if(timer.Get() > 2){
                    timer.Restart();
                }
            }
        } else{
            go->Render();
        }
        // go->box.x += camera.pos.x;
        // go->box.y += camera.pos.y;
    }
}

void TitleState::Start(){
    LoadAssets();
    started = true;
}

void TitleState::Pause(){
    
}

void TitleState::Resume(){
    
}
