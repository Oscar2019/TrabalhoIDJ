#include "Resources.h"
#include "Game.h"
#include "Error.h"
#include <iostream>

Resources::Resources() : 
  imageTable(),
  musicTable(),
  soundTable(),
  fontTable(){
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

std::shared_ptr<SDL_Texture> Resources::GetImage (std::string file){
    auto fileIt = imageTable.find(file);
    if(fileIt != imageTable.end()){
        return fileIt->second;
    } else{
        Game *game = Game::GetInstance(); // pega uma instância do game
        auto texture = IMG_LoadTexture(game->GetRenderer(), file.c_str()); // carrega a imagem
        if(texture == nullptr){ // Se ocorreu um erro Exception
            throw EngineRuntimeError_Line("[Sprite][Open(file)]IMG_LoadTexture: " + std::string(IMG_GetError()) + "\n");
        }
        return imageTable[file] = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
    }
} 

void Resources::ClearImages(){
    for(auto it = imageTable.begin(); it != imageTable.end();){
        if(it->second.unique()){
            it = imageTable.erase(it);
        } else{
            it++;
        }
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

TTF_Font* Resources::GetFont(std::string file, int size){
    auto fileIt = fontTable.find(file + std::to_string(size));
    if(fileIt != fontTable.end()){
        return fileIt->second;
    } else{
        auto font = TTF_OpenFont(file.c_str(), size);
        if(font == nullptr){
            throw EngineRuntimeError_Line("[Resources][TTF_Font*(file, size)]GetFont: " + std::string(TTF_GetError()) + "\n");
        }
        fontTable[file + std::to_string(size)] = font;
        return font;
    } 
}