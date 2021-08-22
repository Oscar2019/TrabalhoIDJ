#include "State.h"

// Construtor default
State::State() : bg(), music(), quitRequested(false){
    
}

// retorna o valor da requisição de saída
bool State::QuitRequested(){
    return quitRequested;
}

// carrega os assts
void State::LoadAssets(){
    bg.Open("assets/img/ocean.jpg");
    music.Open("assets/audio/stageState.ogg");
    music.Play();
}

// atualiza o estado
void State::Update(float dt){
    if(SDL_QuitRequested() == SDL_TRUE){
        quitRequested = true;
    }
}

// renderiza o estado
void State::Render(){
    bg.Render(0, 0);
}
