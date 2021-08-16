#include "Music.h"
#include "Error.h"

Music::Music() : music(nullptr){
}

Music::Music(std::string file) : music(nullptr){
    Open(file);
}

Music::~Music(){
    Mix_FreeMusic(music);
}

void Music::Play(int times){
    if(Mix_PlayMusic(music, times) == -1){
        throw EngineRuntimeError_Line("[Music][Play(times)]Mix_PlayMusic: " + std::string(Mix_GetError()) + "\n");
    }
}

void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr){
        throw EngineRuntimeError_Line("[Music][Open(file)]Mix_LoadMUS: " + std::string(Mix_GetError()) + "\n");
    }
}

bool Music::IsOpen(){
    return music != nullptr;   
}

