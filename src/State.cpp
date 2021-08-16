#include "State.h"

State::State() : bg(), music(), quitRequested(false){
    
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    bg.Open("assets/img/ocean.jpg");
    music.Open("assets/audio/stageState.ogg");
    music.Play();
}

void State::Update(float dt){
    if(SDL_QuitRequested() == SDL_TRUE){
        quitRequested = true;
    }
}

void State::Render(){
    bg.Render(0, 0);
}
