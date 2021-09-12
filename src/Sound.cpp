#include "Sound.h"
#include "Error.h"

const std::string Sound::TYPE = "Sound";

Sound::Sound(GameObject& associated) : Component(associated), chunk(nullptr){
    
}

Sound::Sound(GameObject& associated, std::string file) : Component(associated), chunk(nullptr), channel(-1){
    Open(file);
}

Sound::~Sound(){
    if(chunk != nullptr){
        if(channel != -1){
            Mix_HaltChannel(channel);
        }
        Mix_FreeChunk(chunk);
        chunk = nullptr;
        channel = -1;
    }
}

void Sound::Play(int times){
    channel = Mix_PlayChannel(-1, chunk, times);
    if(channel == -1){ // Se não conseguiur tocar a música erro
        throw EngineRuntimeError_Line("[Sound][Play(times)]Mix_PlayChannel: " + std::string(Mix_GetError()) + "\n");
    }
}

void Sound::Stop(){
    if(chunk == nullptr){
        return;
    }
    Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
    if(chunk != nullptr){
        if(channel != -1){
            Mix_HaltChannel(channel);
        }
        Mix_FreeChunk(chunk);
        chunk = nullptr;
        channel = -1;
    }

    chunk = Mix_LoadWAV(file.c_str());
    if(chunk == nullptr){
        throw EngineRuntimeError_Line("[Sound][Open(file)]Mix_LoadWAV: " + std::string(Mix_GetError()) + "\n");
    }
}

bool Sound::IsOpen(){
    return chunk != nullptr;
}

void Sound::Update(float dt){
    
}

void Sound::Render(){
    
}

bool Sound::Is(std::string type){
    return type == Sound::TYPE;
}
