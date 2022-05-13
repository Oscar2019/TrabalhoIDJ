#pragma once
#include "Component.h"
#include <string>
// #define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER 
// #define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"

class Sound : public Component{
    public:
        static const std::string TYPE;
        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        ~Sound();

        void Play(int times = 0);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        
        void Update(float dt);
        void Render();
        bool Is(std::string type);

    private:
        Mix_Chunk *chunk;
        int channel;
};


