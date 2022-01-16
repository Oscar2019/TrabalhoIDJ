#include "Resources.h"
#include "Game.h"
#include "Error.h"
#include <iostream>

Resources::Resources() : 
  imageTable(),
  musicTable(),
  soundTable(){
}


// Resources::~Resources(){
//     std::cout << "Resource Destructor\n";
//     ClearImages();
//     ClearMusics();
//     ClearSounds();
// }

Resources& Resources::GetInstance(){
    static Resources resources;
    // resources.count++;
    // std::cout << "Resourec Count: " << resources.count << "\n";
    return resources;
}

SDL_Texture* Resources::GetImage (std::string file){
    auto fileIt = imageTable.find(file);
    if(fileIt != imageTable.end()){
        return fileIt->second;
    } else{
        Game *game = Game::GetInstance(); // pega uma instância do game
        auto texture = IMG_LoadTexture(game->GetRenderer(), file.c_str()); // carrega a imagem
        if(texture == nullptr){ // Se ocorreu um erro Exception
            throw EngineRuntimeError_Line("[Sprite][Open(file)]IMG_LoadTexture: " + std::string(IMG_GetError()) + "\n");
        }
        imageTable[file] = texture;
        return texture;
    }
} 

void Resources::ClearImages(){
   for(auto &p : imageTable){
       SDL_DestroyTexture(p.second);
   } 
   imageTable.clear();
}

Mix_Music* Resources::GetMusic (std::string file){
    auto fileIt = musicTable.find(file);
    if(fileIt != musicTable.end()){
        return fileIt->second;
    } else{
        auto music = Mix_LoadMUS(file.c_str());
        if(music == nullptr){
            throw EngineRuntimeError_Line("[Music][Open(file)]Mix_LoadMUS: " + std::string(Mix_GetError()) + "\n");
        }
        musicTable[file] = music;
        return music;
    }
}

void Resources::ClearMusics(){
   for(auto &p : musicTable){
        Mix_FreeMusic(p.second);
   } 
   musicTable.clear();
}

Mix_Chunk* Resources::GetSound (std::string file){
    auto fileIt = soundTable.find(file);
    if(fileIt != soundTable.end()){
        return fileIt->second;
    } else{
        auto chunk = Mix_LoadWAV(file.c_str());
        chunk = Mix_LoadWAV(file.c_str());
        if(chunk == nullptr){
            throw EngineRuntimeError_Line("[Sound][Open(file)]Mix_LoadWAV: " + std::string(Mix_GetError()) + "\n");
        }
        soundTable[file] = chunk;
        return chunk;
    }
} 

void Resources::ClearSounds(){
   for(auto &p : soundTable){
        Mix_FreeChunk(p.second);
   } 
   soundTable.clear();
}
