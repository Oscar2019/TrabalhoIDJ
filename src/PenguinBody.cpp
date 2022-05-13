#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "State.h"
#include "InputManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "State.h"
#include "Sound.h"
#include <iostream>

const std::string PenguinBody::TYPE = "PenguinBody";

PenguinBody::PenguinBody(GameObject& associated) :
  Component(associated),
  player(),
  pcannon(),
  speed(),
  linearSpeed(),
  angle(),
  hp(100){
    player = this;
    Sprite *sprite = new Sprite(associated, "assets//img//penguin.png");
    associated.box.w = sprite->getWidth();
    associated.box.h = sprite->getHeight();
    associated.AddComponent(sprite);

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
}

PenguinBody::~PenguinBody(){
    
}

void PenguinBody::Start(){
    Game *game = Game::GetInstance();
    GameObject *go = new GameObject();
    PenguinCannon *pc = new PenguinCannon(*go, game->GetCurrentState().GetObjectPtr(&associated));
    go->AddComponent(pc);
    pcannon = game->GetCurrentState().AddObject(go);
}

void PenguinBody::Update(float dt){
    InputManager &input = InputManager::GetInstance();
    const float pi = acos(-1);
    const float acceleration = 20;
    const float angularSpeed = pi;
    const float limitSpeed = 100;

    if(input.IsKeyDown(W_KEY)){
        linearSpeed += acceleration * dt;
        if(linearSpeed >= limitSpeed){
            linearSpeed = limitSpeed;
        } 
    }
    if(input.IsKeyDown(S_KEY)){
        linearSpeed -= acceleration * dt;
        if(linearSpeed <= -limitSpeed){
            linearSpeed = -limitSpeed;
        }
    }
    if(input.IsKeyDown(A_KEY)){
        angle += angularSpeed * dt;
    }
    if(input.IsKeyDown(D_KEY)){
        angle -= angularSpeed * dt;
    }
    if(angle >= 2*pi){
      angle -= 2*pi;
    } else if(angle < 0){
      angle += 2*pi;
    }
    associated.angleDeg = angle / pi * 180;

    if(abs(linearSpeed) <= 0.0001){
        linearSpeed = 0;
    }

    speed = Vec2(1, 0);
    speed = Vec2::rotate(speed, angle) * linearSpeed;
    
    if(associated.box.x + speed.x * dt < 0){
        associated.box.x = 0;
        speed.x = 0;
    } else if(associated.box.x + speed.x * dt >= 1408){
        associated.box.x = 1408;
        speed.x = 0;
    } else{
        associated.box.x += speed.x * dt;
    }
    if(associated.box.y + speed.y * dt < 0){
        associated.box.y = 0;
        speed.y = 0;
    } else if(associated.box.y + speed.y * dt >= 1280){
        associated.box.y = 1280;
        speed.y = 0;
    } else{
        associated.box.y += speed.y * dt;
    }

    // std::cout << "associated.box.x " << associated.box.x << "\n";
    // std::cout << "associated.box.y " << associated.box.y << "\n";
    // std::cout << "associated.box.w " << associated.box.w << "\n";
    // std::cout << "associated.box.h " << associated.box.h << "\n";
    /*
        associated.box.x 24.1204
        associated.box.y -16.3122

        associated.box.x 1304.38
        associated.box.y 1181.12
    */
    if(hp <= 0){
        associated.RequestDelete();
        player = nullptr;
        Camera &camera = Camera::GetInstance(1);
        camera.Unfollow();

        GameObject *go = new GameObject();
        go->box = associated.box;
        Sprite *sprite = new Sprite(*go, "assets/img/penguindeath.png", 5, 0.14, 0.7);
        go->angleDeg = associated.angleDeg;
        go->AddComponent(sprite);

        Sound *sound = new Sound(*go, "assets/audio/boom.wav");
        sound->Play();
        go->AddComponent(sound);

        Game *game = Game::GetInstance();
        game->GetCurrentState().AddObject(go);
    }
}

void PenguinBody::Render(){
    
}

bool PenguinBody::Is(std::string type){
    return type == PenguinBody::TYPE;
} 

void PenguinBody::NotifyCollision(GameObject& other){
    Bullet *bullet = dynamic_cast<Bullet*>(other.GetComponent(Bullet::TYPE));
    if(bullet != nullptr && bullet->targetsPlayer){
        hp -= 10;
    }
}
