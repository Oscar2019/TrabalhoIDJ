#pragma once
#include <SDL2/SDL.h>
#include <string>

class Sprite{
    public:
        Sprite();
        Sprite(std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y);
        int getWidth();
        int getHeight();
        bool IsOpen();
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};
