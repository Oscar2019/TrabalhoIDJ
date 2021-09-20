#include "Face.h"
#include "GameObject.h"
#include "Sound.h"
#include <SDL2/SDL.h>

const std::string Face::TYPE = "Face";

Face::Face(GameObject &associated) : Component(associated), hitpoints(0){
    
}

void Face::Damage(int damage){
    hitpoints -= damage;
    if(hitpoints <= 0){
        Sound *sound = dynamic_cast<Sound*>(associated.GetComponent(Sound::TYPE));
        sound->Play();
        SDL_Delay(800);
        associated.RequestDelete();
    }
}

void Face::Update(float dt){
    
}

void Face::Render(){
    
}

bool Face::Is(std::string type){
    return type == Face::TYPE;
}
