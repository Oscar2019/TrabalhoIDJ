#pragma once
#include <string>
#include <memory>
#define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER 
// #define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"
#include "Camera.h"

class State{
    public:
        State();
        virtual ~State();
        
        virtual void LoadAssets() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        
        virtual void Start() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;
        
        virtual std::weak_ptr<GameObject> AddObject(GameObject* go);
        virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
        
        bool QuitRequested();
        bool PopRequested();
    
    protected:

        void StartArray();
        void UpdateArray();
        void RenderArray();
    
        bool popRequested;
        bool quitRequested;
        bool started;
        
        std::vector<std::shared_ptr<GameObject>> objectArray;

};
