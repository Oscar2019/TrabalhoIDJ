#include "Bullet.h"
#include "Sprite.h"
#include "PenguinBody.h"
#include "Alien.h"
#include "Collider.h"
#include <iostream>


const std::string Bullet::TYPE = "Bullet";

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int qtdAnimation, int animationSpeed) :
  Component(associated),
  speed(),
  distanceLeft(maxDistance),
  damage(damage),
  targetsPlayer(false){
    Sprite *spr = new Sprite(associated, sprite, qtdAnimation, animationSpeed);
    associated.AddComponent(spr);
    associated.box.h = spr->getHeight();
    associated.box.w = spr->getWidth();
    associated.box.x -= associated.box.h / 2;
    associated.box.y -= associated.box.w / 2;
    Vec2 vec(400, 0);
    auto ret = Vec2::rotate(vec, angle);
    associated.angleDeg = angle*180/acos(-1);
    this->speed = ret * speed * 0.3;

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
}

void Bullet::Update(float dt){
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    distanceLeft -= Vec2::magnitude(speed) * dt; 
    if(abs(distanceLeft) <= Vec2::magnitude(speed) * dt){
        associated.RequestDelete();
    }
}

void Bullet::Render(){
    
}

bool Bullet::Is(std::string type){
    return Bullet::TYPE == type;
}

int Bullet::GetDamage(){
    return damage;
}


void Bullet::NotifyCollision(GameObject& other){
    if(targetsPlayer && other.GetComponent(PenguinBody::TYPE) != nullptr){
        associated.RequestDelete();
    } else if(!targetsPlayer && other.GetComponent(Alien::TYPE) != nullptr){
        associated.RequestDelete();
    }
}

