#pragma once
#include <string>
#include <unordered_map>
#include "Include.h"

class Resources{
    public:
        static Resources& GetInstance();
        // ~Resources();
        SDL_Texture* GetImage (std::string file); 
        void ClearImages();
        Mix_Music* GetMusic (std::string file);
        void ClearMusics();
        Mix_Chunk* GetSound (std::string file); 
        void ClearSounds();
        // int count = 0;
    private:
        Resources();
        std::unordered_map<std::string, SDL_Texture*> imageTable;
        std::unordered_map<std::string, Mix_Music*> musicTable;
        std::unordered_map<std::string, Mix_Chunk*> soundTable;
};