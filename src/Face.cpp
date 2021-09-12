#include "Face.h"
#include "GameObject.h"

const std::string Face::TYPE = "Face";

Face::Face(GameObject &associated) : Component(associated), hitpoints(0){
    
}

void Face::Damage(int damage){
    hitpoints -= damage;
    if(hitpoints <= 0){
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
