#include "State.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Face.h"
#include "Game.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Game.h"
#include "Sound.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"
#include "PenguinCannon.h"
#include "Bullet.h"
#include "Minion.h"
#include <iostream>

// Construtor default
State::State() : 
  popRequested(),
  quitRequested(),
  started(),
  objectArray(){
      
}


State::~State(){
    objectArray.clear();
}

bool State::PopRequested(){
    return popRequested;
}

// retorna o valor da requisição de saída
bool State::QuitRequested(){
    return quitRequested;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    std::shared_ptr<GameObject> ptr(go);
    objectArray.push_back(ptr);
    if(started){
        go->Start();
    }
    return ptr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
    // std::cout << "hoisada1n" << std::endl;
    for(auto obj : objectArray){
        if(obj.get() == go){
            // std::cout << "hoi1n" << std::endl;
            return obj;
        }
    }
    return {};
}

