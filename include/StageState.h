#pragma once
#include <string>
#include <memory>
#define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER 
// #define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"
#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"
#include "Timer.h"
#include "Camera.h"

class StageState : public State{
    public:
        StageState();
        ~StageState();

        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();

        std::weak_ptr<GameObject> player;
        Camera &camera;
    private:
        TileSet* tileSet;
        Music backgroundMusic; 
        GameObject* goTileMap;
        Timer timer;
};

