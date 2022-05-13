#include "Game.h"
#include "State.h"
#include "InputManager.h"
#include "Error.h"
#include "Resources.h"
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER 
#define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"
#include <stdio.h>

Game *Game::instance = nullptr; // inicializa a instância com um ponteiro nulo

// Cria uma instância de um game 
Game::Game(std::string title, int width, int height) : 
  window(nullptr), 
  renderer(nullptr), 
  storedState(nullptr),
  frameStart(),
  dt(),
  width(width),
  height(height){
    int flags_mask = 0;
    
    // Inicializa o vídeo, aúdio e timer do SDl
    flags_mask = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER; 
    if(SDL_Init(flags_mask) < 0){ // Se houver erro gera uma exceção
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_Init: " + std::string(SDL_GetError()) + "\n");
    }

    // Inicializa o jpg, png e tif do SDl_IMG
    flags_mask = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if((IMG_Init(flags_mask) & flags_mask) != flags_mask){ // Se houver erro gera uma exceção
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]IMG_Init: " + std::string(IMG_GetError()) + "\n");
    }

    // Inicializa o mod, mp3 e ogg do SDl_MIX
    flags_mask = MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
    if((Mix_Init(flags_mask) & flags_mask) != flags_mask){ // Se houver erro gera uma exceção
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]Mix_Init: " + std::string(Mix_GetError()) + "\n");
    }
    
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]Mix_OpenAudio: " + std::string(Mix_GetError()) + "\n");
    }
    Mix_AllocateChannels(32);

    if(TTF_Init()){
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]TTF_Init: " + std::string(TTF_GetError()) + "\n");
    }

    // Cria uma janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr){ // Se houver erro gera uma exceção
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_CreateWindow: " + std::string(SDL_GetError()) + "\n");
    }

    // Cria um rendere
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){ // Se houver erro gera uma exceção
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_CreateRenderer: " + std::string(SDL_GetError()) + "\n");
    }

}

Game::~Game(){
    if(storedState != nullptr){
        delete storedState;
    }
    SDL_DestroyRenderer(renderer); // destroy renderer
    SDL_DestroyWindow(window); // destro a janela

    Mix_CloseAudio(); 

    TTF_Quit(); // fecha o SDL_TTF

    Mix_Quit(); // fecha o SDL_MIX

    IMG_Quit(); // fecha o SDL_IMG

    SDL_Quit(); // fecha o SDL
}

// carrega o game
void Game::Run(){
    while(true){

        if(storedState != nullptr){
            stateStack.emplace(storedState);
            storedState = nullptr;
        }
        if(stateStack.empty()){
            break;
        }
        State &state = *stateStack.top();
        if(state.QuitRequested()){
            while(!stateStack.empty()){
                stateStack.pop();
            }
            break;
        }
        state.Start();
        while(!state.QuitRequested() && !state.PopRequested() && storedState == nullptr){ // enquanto o usuári não apertar para fechar
            CalculaDeltaTime();
            InputManager::GetInstance().Update();
            state.Update(dt); // update o stado do jogo
            state.Render(); // renderiza o estado dojogo
            SDL_RenderPresent(renderer); 
            SDL_Delay(33); // espera 33 ms
        }
        if(state.PopRequested()){
            stateStack.pop();
        }
        if(storedState != nullptr){
            storedState->Pause();
        }
        auto resources = Resources::GetInstance();
        resources.ClearImages();
    }
    if(storedState != nullptr){
        stateStack.emplace(storedState);
        storedState = nullptr;
    }
    while(!stateStack.empty()){
        stateStack.pop();
    }
	auto resources = Resources::GetInstance();
	resources.ClearImages();
	resources.ClearSounds();
	resources.ClearMusics();
}

// retorna o renderer
SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

// Retorna o estado do jogo
State& Game::GetCurrentState(){
    return *stateStack.top();
}

// retora o singleton
Game* Game::GetInstance(){
    if(Game::instance == nullptr){
        return Game::instance = new Game("Oscar|170112209", 1024, 600);
    }
    return Game::instance;
}

void Game::CalculaDeltaTime(){
    int next_frameStart = SDL_GetTicks();
    dt = (next_frameStart - frameStart) / 1000.0f;
    frameStart = next_frameStart;
}

float Game::GetDeltaTime(){
    return dt;
}


int Game::GetWidth(){
    return width;
}

int Game::GetHeight(){
    return height;
}

void Game::Push(State* state){
    storedState = state;
}




