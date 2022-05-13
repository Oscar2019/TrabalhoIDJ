#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER 
#define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"

class Resources{
    public:
        static Resources& GetInstance();
        // ~Resources();
        std::shared_ptr<SDL_Texture> GetImage (std::string file); 
        void ClearImages();
        Mix_Music* GetMusic(std::string file);
        void ClearMusics();
        Mix_Chunk* GetSound(std::string file); 
        void ClearSounds();
        TTF_Font* GetFont(std::string file, int size); 
        void ClearFonts();
        // int count = 0;
    private:
        Resources();
        std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        std::unordered_map<std::string, Mix_Music*> musicTable;
        std::unordered_map<std::string, Mix_Chunk*> soundTable;
        std::unordered_map<std::string, TTF_Font*> fontTable;
};