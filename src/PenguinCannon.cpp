#include "PenguinCannon.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Collider.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"
#include <iostream>


const std::string PenguinCannon::TYPE = "PenguinCannon";

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) :
  Component(associated),
  pbody(penguinBody),
  angle(0), 
  timer(){
    Sprite *sprite = new Sprite(associated, "assets\\img\\cubngun.png");
    associated.box.w = sprite->getWidth();
    associated.box.h = sprite->getHeight();
    associated.box.x = (pbody.lock()->box.w - associated.box.w) / 2 + pbody.lock()->box.x;
    associated.box.y = (pbody.lock()->box.h - associated.box.h) / 2 + pbody.lock()->box.y;
    associated.AddComponent(sprite);

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
}

PenguinCannon::~PenguinCannon(){
    
}

void PenguinCannon::Update(float dt){
    InputManager &input = InputManager::GetInstance();
    Camera &camera = Camera::GetInstance(1);
    const float pi = acos(-1);
    timer.update(dt);
    if(pbody.expired()){
        associated.RequestDelete();
        return;
    }

    Vec2 pos{};
    // associated.box.x = (pbody.lock()->box.x - associated.box.w) / 2 + pbody.lock()->box.x;
    // associated.box.y = (pbody.lock()->box.y - associated.box.h) / 2 + pbody.lock()->box.y;
    pos.x = associated.box.x = (pbody.lock()->box.w - associated.box.w) / 2 + pbody.lock()->box.x;
    pos.y = associated.box.y = (pbody.lock()->box.h - associated.box.h) / 2 + pbody.lock()->box.y;

    Vec2 mousePos{};
    mousePos.x = input.GetMouseX() + camera.pos.x;
    mousePos.y = input.GetMouseY() + camera.pos.y;

    
    angle = Vec2::inclination(mousePos-(pos+(Vec2(associated.box.w, associated.box.h) * 0.5)));
    associated.angleDeg = angle / pi * 180;
    
    if(timer.Get() >= 0.5 && input.MousePress(LEFT_MOUSE_BUTTON)){
        timer.Restart();
        Shoot();
    }
}

void PenguinCannon::Render(){
    
}

bool PenguinCannon::Is(std::string type){
    return type == PenguinCannon::TYPE;
} 

void PenguinCannon::Shoot(){
    
    // // target.y = -target.y;
    Vec2 center = Rect::center(associated.box);
    Vec2 myBox = Vec2::rotate(Vec2(associated.box.x + associated.box.w, associated.box.y + associated.box.h / 2) - center, angle) + center;
    // // Vec2 source(associated.box.x, associated.box.y);
    // auto arc = Vec2::inclination(target - myBox);
    // // std::cout << arc / acos(-1) * 180 << "\n";
    // // auto arc = acos((source * target) / (Vec2::magnitude(source) * Vec2::magnitude(target)));
    // // auto arc = this->arc + acos((source * target) / (Vec2::magnitude(source) * Vec2::magnitude(target)));
    GameObject *go = new GameObject();
    go->box.x = myBox.x;
    go->box.y = myBox.y;
    Bullet *bullet = new Bullet(*go, angle, 1.0f, 10, 1000, "assets\\img\\penguinbullet.png", 4, 0.75);
    go->AddComponent(bullet);
    Game::GetInstance()->GetState().AddObject(go);
}
