#include "Collider.h"
#include "Geometry.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Game.h"
#include "Camera.h"

const std::string Collider::TYPE = "Collider";
Collider::Collider(GameObject& associated, Vec2 scale,  Vec2 offset) :
  Component(associated),
  box(),
  scale(scale),
  offset(offset){
    
}

void Collider::Update(float dt){
    const float pi = acos(-1);
    
    box.w = associated.box.w * scale.x;
    box.h = associated.box.h * scale.y;
    
    box.x = associated.box.x + (associated.box.w - box.w) / 2;
    box.y = associated.box.y + (associated.box.h - box.h) / 2;
    
    Vec2 res = Vec2::rotate(offset, associated.angleDeg / 180 * pi);
    box.x += res.x;
    box.y += res.y;
}

void Collider::Render(){
#ifdef DEBUG
    Vec2 center(Rect::center(box));
    SDL_Point points[5];
    Camera &camera = Camera::GetInstance(1);


    Vec2 point = Vec2::rotate(Vec2(box.x, box.y) - center,  associated.angleDeg/(180/PI))
            + center - camera.pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};
    
    point = Vec2::rotate(Vec2(box.x + box.w, box.y) - center, associated.angleDeg/(180/PI) )
            + center - camera.pos;
    points[1] = {(int)point.x, (int)point.y};
    
    point = Vec2::rotate(Vec2(box.x + box.w, box.y + box.h) - center, associated.angleDeg/(180/PI) )
            + center - camera.pos;
    points[2] = {(int)point.x, (int)point.y};
    
    point = Vec2::rotate(Vec2(box.x, box.y + box.h) - center, associated.angleDeg/(180/PI) )
            + center - camera.pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance()->GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type){
    return Collider::TYPE == type;
}

void Collider::SetScale(Vec2 scale){
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset){
    this->offset = offset;
}
