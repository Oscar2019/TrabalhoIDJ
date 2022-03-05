
#include "Camera.h"
#include "Geometry.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

std::map<int, Camera*> Camera::instances;

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
        Game *game = Game::GetInstance();
        Vec2 aux(game->GetWidth(), game->GetHeight());
        aux *= 0.5;
        pos = Rect::center(focus->box) - aux; 
    } else{
        InputManager &input = InputManager::GetInstance();
        speed.x = 0;
        speed.y = 0;
        if(input.IsKeyDown(LEFT_ARROW_KEY)){
            speed.x = - 100*dt;
        } else if(input.IsKeyDown(RIGHT_ARROW_KEY)){
            speed.x = + 100*dt;
        } else if(input.IsKeyDown(UP_ARROW_KEY)){
            speed.y = - 100*dt;
        } else if(input.IsKeyDown(DOWN_ARROW_KEY)){
            speed.y = + 100*dt;
        }
        pos.x += speed.x;
        pos.y += speed.y;
    }
}

Camera& Camera::GetInstance(int instNum){
    if(Camera::instances[instNum] == nullptr){
        Camera::instances[instNum] = new Camera();
    }
    return *Camera::instances[instNum];
}