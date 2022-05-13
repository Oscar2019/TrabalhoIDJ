#include "Music.h"
#include "Error.h"
#include "Resources.h"

// construtor default
Music::Music() : music(nullptr){
}

// construtor que abri um audio
Music::Music(std::string file) : music(nullptr){
    Open(file);
}

// libera a música aberta
Music::~Music(){
    Stop();
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
    auto resources = Resources::GetInstance();
    music = resources.GetMusic(file);
}

// Verifica se uma musica está aberta
bool Music::IsOpen(){
    return music != nullptr;   
}

