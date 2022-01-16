#include "Minion.h"
#include "Game.h"
#include "State.h"
#include "Bullet.h"
#include <iostream>

const std::string Minion::TYPE = "Minion";


Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) :
  Component(associated),
  alienCenter(alienCenter),
  arc(arcOffsetDeg), 
  root(), 
  myCenter(){
    Sprite *sprite = new Sprite(associated, "assets\\img\\minion.png");
    associated.box.x = 0;
    associated.box.y = 0;
    associated.box.h = sprite->getHeight();
    associated.box.w = sprite->getWidth();
    associated.AddComponent(sprite);

    float scale = 1 + rand() / (2.0 * RAND_MAX);
    root = 100 + sprite->getWidth() * (scale - 1) / 2;
    Vec2 vec(root, 0);
    // std::cout << root << "\n";
    myCenter.x = sprite->getWidth() / 2 * scale;
    myCenter.y = sprite->getHeight() / 2 * scale;

    sprite->SetScaleX(scale, scale);
    // associated.box.h = sprite->getHeight();
    // associated.box.w = sprite->getWidth();


    auto ret = Vec2::rotate(vec, arc);
    auto box = Rect::center(alienCenter.lock()->box);
    // auto myCenter = Rect::center(associated.box);
    associated.box.x = box.x + ret.x - myCenter.x;
    associated.box.y = box.y + ret.y - myCenter.y;
    // associated.box.x = box.x + ret.x;
    // associated.box.y = box.y + ret.y;
}

void Minion::Update(float dt){
    const auto pi = acos(-1);
    arc += pi / 4 * dt;
    // arc += pi / 4;
    
    if(arc > 2 * pi){
        arc -= 2 * pi;
    }
    associated.angleDeg = -arc*180/pi;
    associated.box.x = 0;
    associated.box.y = 0;
    Vec2 vec(root, 0);
    auto ret = Vec2::rotate(vec, arc);
    auto box = Rect::center(alienCenter.lock()->box);
    // auto myCenter = Rect::center(associated.box);
    associated.box.x = box.x + ret.x - myCenter.x;
    associated.box.y = box.y + ret.y - myCenter.y;
    // associated.box.x = box.x + ret.x;
    // associated.box.y = box.y + ret.y;
}

void Minion::Render(){
}

bool Minion::Is(std::string type){
    return Minion::TYPE == type;
}

void Minion::Shoot(Vec2 target){
    // target.y = -target.y;
    Vec2 myBox(associated.box.x + associated.box.w / 2, associated.box.y + associated.box.h / 2);
    // Vec2 source(associated.box.x, associated.box.y);
    auto arc = - Vec2::inclination(target - myBox);
    // std::cout << arc / acos(-1) * 180 << "\n";
    // auto arc = acos((source * target) / (Vec2::magnitude(source) * Vec2::magnitude(target)));
    // auto arc = this->arc + acos((source * target) / (Vec2::magnitude(source) * Vec2::magnitude(target)));
    GameObject *go = new GameObject();
    go->box.x = myBox.x;
    go->box.y = myBox.y;
    Bullet *bullet = new Bullet(*go, (float)arc, 1.0f, 10, Vec2::distance(myBox, target), "assets\\img\\minionbullet1.png");
    go->AddComponent(bullet);
    Game::GetInstance()->GetState().AddObject(go);
}

