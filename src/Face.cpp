#include "Face.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Sound.h"
#define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER 
// #define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"

const std::string Face::TYPE = "Face";

Face::Face(GameObject &associated) : Component(associated), hitpoints(0){
    
}

void Face::Damage(int damage){
    hitpoints -= damage;
    if(hitpoints <= 0){
        Sound *sound = dynamic_cast<Sound*>(associated.GetComponent(Sound::TYPE));
        sound->Play();
        associated.RequestDelete();
    }
}

void Face::Update(float dt){
    // InputManager &input = InputManager::GetInstance();
	// int mouseX = input.GetMouseX();
    // int mouseY = input.GetMouseY();

    // if(input.IsMouseDown(LEFT_MOUSE_BUTTON) && Rect::is_inside(associated.box, {(float)mouseX, (float)mouseY} ) ) {
    //     Damage(std::rand() % 10 + 10);
    // }

    // if(input.KeyPress(SDLK_LEFT)){
    //     associated.box.x += 10;
    // }
    // if(input.KeyPress(SDLK_RIGHT)){
    //     associated.box.x -= 10;
    // }
    // if(input.KeyPress(SDLK_UP)){
    //     associated.box.y += 10;
    // }
    // if(input.KeyPress(SDLK_DOWN)){
    //     associated.box.y -= 10;
    // }

}

void Face::Render(){
    
}

bool Face::Is(std::string type){
    return type == Face::TYPE;
}
