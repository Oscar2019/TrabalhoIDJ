// #pragma once
// #include <string>
// #include <memory>
// #include <SDL2/SDL.h>
// #include "Sprite.h"
// #include "Music.h"
// #include "GameObject.h"
// #include "TileSet.h"
// #include "Camera.h"

// class State{
//     public:
//         State();
//         ~State();
        
//         void Start();
//         void LoadAssets();
//         void Update(float dt);
//         void Render();

//         std::weak_ptr<GameObject> player;
//         Camera &camera;
//     private:
//         void Input();
//         void AddObject(int mouseX, int mouseY);

//         bool started;
//         std::vector<std::shared_ptr<GameObject>> objectArray;

        
//         // Sprite *bg;
//         GameObject* goTileMap;
//         TileSet *tileSet;
//         Music music;
//         bool quitRequested;
// };
