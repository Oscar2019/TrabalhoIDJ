#pragma once
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"
#include "Camera.h"

class State{
    public:
        State();
        ~State();
        bool QuitRequested();
        
        void LoadAssets();
        void Update(float dt);
        void Render();

        Camera camera;
    private:
        void Input();
        void AddObject(int mouseX, int mouseY);

        std::vector<std::unique_ptr<GameObject>> objectArray;

        
        // Sprite *bg;
        GameObject* goTileMap;
        Music music;
        bool quitRequested;
        TileSet *tileSet;
};
