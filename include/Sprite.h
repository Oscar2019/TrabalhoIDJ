#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER 
// #define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"
#include <string>
#include <memory>
#include "Component.h"
#include "Timer.h"
#include "Geometry.h"

class Sprite : public Component{
    public:
        static const std::string TYPE;
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
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

        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScaleY();
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
    private:
        std::shared_ptr<SDL_Texture> texture;
        int width;
        int height;
        SDL_Rect clipRect;
        Vec2 scale;
        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;
        float secondsToSelfDestruct;
        Timer selfDestructCount;
};
