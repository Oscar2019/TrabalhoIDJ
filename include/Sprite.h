#pragma once
#include <SDL2/SDL.h>
#include <string>
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
        SDL_Texture* texture;
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
