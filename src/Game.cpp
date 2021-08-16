#include "Game.h"
#include "State.h"
#include "Error.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) : window(nullptr), renderer(nullptr), state(nullptr){
    int flags = 0;
    
    flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
    if(SDL_Init(flags) < 0){
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_Init: " + std::string(SDL_GetError()) + "\n");
    }

    flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if((IMG_Init(flags) & flags) != flags){
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]IMG_Init: " + std::string(IMG_GetError()) + "\n");
    }

    flags = MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
    if((Mix_Init(flags) & flags) != flags){
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]Mix_Init: " + std::string(Mix_GetError()) + "\n");
    }
    
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]Mix_OpenAudio: " + std::string(Mix_GetError()) + "\n");
    }
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr){
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_CreateWindow: " + std::string(SDL_GetError()) + "\n");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_CreateRenderer: " + std::string(SDL_GetError()) + "\n");
    }

    state = new State();

}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();

    Mix_Quit();

    IMG_Quit();

    SDL_Quit();
}

void Game::Run(){
    state->LoadAssets();
    while(!state->QuitRequested()){
        state->Update(0.0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

State& Game::GetState(){
    return *state;
}

Game* Game::GetInstance(){
    if(Game::instance == nullptr){
        Game::instance = new Game("Oscar|170112209", 1024, 600);
    }
    return Game::instance;
}