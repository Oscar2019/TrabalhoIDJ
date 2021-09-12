#pragma once
#include "Component.h"
#include <string>
#include <SDL2/SDL_mixer.h>

class Sound : public Component{
    public:
        static const std::string TYPE;
        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        ~Sound();

        void Play(int times = 1);
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


