#pragma once
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

class State{
    public:
        State();
        ~State();
        bool QuitRequested();
        
        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        void Input();
        void AddObject(int mouseX, int mouseY);

        std::vector<std::unique_ptr<GameObject>> objectArray;

        Sprite bg;
        Music music;
        bool quitRequested;
};
