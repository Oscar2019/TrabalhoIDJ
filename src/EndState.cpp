#include "EndState.h"
#include "GameData.h"
#include "Text.h"
#include "InputManager.h"
#include "Timer.h"
#include "Game.h"
#include <iostream>

EndState::EndState():
  State(),
  backgroundMusic(), 
  timer(){
    
}

EndState::~EndState(){
    
}

void EndState::LoadAssets(){
    std::string imageFileName;
    std::string soundFileName;
    if(gameData.playerVictory){
        imageFileName = "assets/img/win.jpg";
        soundFileName = "assets/audio/endStateWin.ogg";
    } else{
        imageFileName = "assets/img/lose.jpg";
        soundFileName = "assets/audio/endStateLose.ogg";
    }

    GameObject *go = nullptr;
    go = new GameObject();
    Sprite *bg = new Sprite(*go, imageFileName.c_str());
    go->box.x = 0;
    go->box.y = 0;
    go->box.w = bg->getWidth();
    go->box.h = bg->getHeight();
    go->AddComponent(bg);
    AddObject(go);

    go = new GameObject();
    Text *text = new Text(*go, "assets/font/Call me maybe.ttf", 36, TextStyle::SOLID, "Precione ESQ para sair", SDL_Color{50,80,20,255});
    go->box.x = 331;
    go->box.y = 420;
    go->AddComponent(text);
    AddObject(go);

    go = new GameObject();
    text = new Text(*go, "assets/font/Call me maybe.ttf", 36, TextStyle::SOLID, "Precione SPACE para voltar ao menu", SDL_Color{50,80,20,255});
    go->box.x = 220;
    go->box.y = 510;
    go->AddComponent(text);
    AddObject(go);

    backgroundMusic.Open(soundFileName.c_str());
    backgroundMusic.Play();
}

void EndState::Update(float dt){
    timer.update(dt);
    InputManager& input = InputManager::GetInstance();
    quitRequested = input.QuitRequested() || input.KeyRelease(ESCAPE_KEY);
    popRequested = input.KeyPress(SPACE_KEY);
    if(popRequested){
        backgroundMusic.Stop();
    }
}

void EndState::Render(){
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

void EndState::Start(){
    LoadAssets();
}

void EndState::Pause(){
    
}

void EndState::Resume(){
    
}


