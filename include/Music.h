#pragma once

#include <string>
// #define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER 
// #define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"

class Music{
    public:
        Music();
        Music(std::string file);
        ~Music();

        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(std::string file);
        bool IsOpen();
    
    private:
        Mix_Music *music;
};