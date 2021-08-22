#include "Music.h"
#include "Error.h"

// construtor default
Music::Music() : music(nullptr){
}

// construtor que abri um audio
Music::Music(std::string file) : music(nullptr){
    Open(file);
}

// libera a música aberta
Music::~Music(){
    if(music != nullptr){
        Mix_FreeMusic(music);
    }
}

// toca a música
void Music::Play(int times){
    if(Mix_PlayMusic(music, times) == -1){ // Se não conseguiur tocar a música erro
        throw EngineRuntimeError_Line("[Music][Play(times)]Mix_PlayMusic: " + std::string(Mix_GetError()) + "\n");
    }
}

// Para de tocar a música
void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

// Abre um arquivo de música
void Music::Open(std::string file){
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr){
        throw EngineRuntimeError_Line("[Music][Open(file)]Mix_LoadMUS: " + std::string(Mix_GetError()) + "\n");
    }
}

// Verifica se uma musica está aberta
bool Music::IsOpen(){
    return music != nullptr;   
}

