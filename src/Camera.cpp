
#include "Camera.h"
#include "Geometry.h"
#include "GameObject.h"
#include "InputManager.h"
#include <SDL2/SDL.h>


Camera::Camera():
  pos{},
  speed{},
  focus(nullptr){

}

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;    
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if(focus != nullptr){
        pos = Rect::center(focus->box); 
    } else{
        InputManager &input = InputManager::GetInstance();
        speed.x = 0;
        speed.y = 0;
        if(input.IsKeyDown(LEFT_ARROW_KEY)){
            speed.x = - 1*dt;
        } else if(input.IsKeyDown(RIGHT_ARROW_KEY)){
            speed.x = + 1*dt;
        } else if(input.IsKeyDown(UP_ARROW_KEY)){
            speed.y = - 1*dt;
        } else if(input.IsKeyDown(DOWN_ARROW_KEY)){
            speed.y = + 1*dt;
        }
        pos.x += speed.x;
        pos.y += speed.y;
    }
}
