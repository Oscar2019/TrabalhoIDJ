#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Component.h"

class Sprite : public Component{
    public:
        static const std::string TYPE;
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y, int w, int h);
        void Render(int x, int y);
        int getWidth();
        int getHeight();
        bool IsOpen();
        
        void Update(float dt);
        void Render();
        bool Is(std::string type);
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};
