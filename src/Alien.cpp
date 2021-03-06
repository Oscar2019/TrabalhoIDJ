#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"
#include "State.h"
#include "Collider.h"
#include "Sound.h"
#include "State.h"
#include "StageState.h"
#include "Bullet.h"
#include <iostream>

const std::string Alien::TYPE = "Alien";
int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions):
  Component(associated),
  speed(),
  hp(100),
  minionArray(nMinions),
  state(RESTING),
  restTimer(),
  destination(){
    alienCount++;
    Sprite *sprite = new Sprite(associated, "assets//img//alien.png");
    associated.box.x = 512;
    associated.box.y = 300;
    associated.box.h = sprite->getHeight();
    associated.box.w = sprite->getWidth();
    // std::cout << (associated.box.x +  associated.box.h) / 2 << " ";
    // std::cout << (associated.box.y + associated.box.w) / 2 << "\n";
    // std::cout << "assets//img//alien.png\n";
    associated.AddComponent(sprite);
    // std::cout << "assets//img//alien.png\n";

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
}

Alien::~Alien(){
    alienCount--;
}

void Alien::Start(){
    GameObject *go = nullptr;
    Minion *minionPtr = nullptr;
    Game *game = Game::GetInstance();
    for(int i = 0; i < minionArray.size(); i++){
        auto &minion = minionArray[i];
        float pi = acos(-1);
        go = new GameObject();

        minionPtr = new Minion(*go, game->GetCurrentState().GetObjectPtr(&associated), (2 * pi * i) /  minionArray.size());
        // std::cout << ((2 * pi * i) /  minionArray.size()) * 180 / acos(-1) << "\n"; 
        go->AddComponent(minionPtr);
        minion = game->GetInstance()->GetCurrentState().AddObject(go); 
    }
}

void Alien::Update(float dt){
    Camera &camera = Camera::GetInstance(1);
    const auto pi = acos(-1);
    associated.angleDeg += 180.0 / 8 * dt;
    InputManager &input = InputManager::GetInstance();
    Game *game = Game::GetInstance();
    StageState &gameState = dynamic_cast<StageState&>(game->GetCurrentState());
    
    if(state == AlienState::RESTING){
        restTimer.update(dt);
        if(restTimer.Get() >= 0.5){
            restTimer.Restart();
            if(!gameState.player.expired()){
                destination.x = gameState.player.lock()->box.x;
                destination.y = gameState.player.lock()->box.y;
                state = AlienState::MOVING;
            } 
        }
    } else if(state == MOVING){
            auto curPos = Rect::center(associated.box);
            auto dist = destination - curPos;
            if(Vec2::magnitude(dist) <= Vec2::magnitude(speed) * dt){
                speed = Vec2();
                associated.box.x = destination.x - associated.box.w / 2;
                associated.box.y = destination.y - associated.box.h / 2;
                Vec2 penguinPos(gameState.player.lock()->box.x, gameState.player.lock()->box.y);
                state = AlienState::RESTING;

                auto peguinDist = INFINITY;
                std::shared_ptr<GameObject> minion;
                for(int i = 0; i < minionArray.size(); i++){
                    if(!minionArray[i].expired()){
                        auto minionAux = minionArray[i].lock();
                        Vec2 minionPos(minionAux->box.x, minionAux->box.y);
                        auto auxDist = Vec2::distance(penguinPos, minionPos);
                        if(peguinDist > auxDist){
                            peguinDist = auxDist;
                            minion = minionAux;
                        }
                    }
                }
                Minion *curMinion = dynamic_cast<Minion*>(minion->GetComponent(Minion::TYPE));
                curMinion->Shoot(penguinPos);
            } else{
                speed = Vec2::normalize(dist) * 40;
                associated.box.x += speed.x * dt;
                associated.box.y += speed.y * dt;
            }
    }

    // if (input.MousePress(LEFT_MOUSE_BUTTON)){
    //     taskQueue.emplace(Action::SHOOT, input.GetMouseX() + camera.pos.x, input.GetMouseY() + camera.pos.y);
    // }
    // if (input.MousePress(RIGHT_MOUSE_BUTTON)){
    //     taskQueue.emplace(Action::MOVE, input.GetMouseX() + camera.pos.x, input.GetMouseY() + camera.pos.y);
    // }
    
    // if(!taskQueue.empty()){
    //     auto action = taskQueue.front();
    //     auto curPos = Rect::center(associated.box);
    //     auto dist = action.pos - curPos;
    //     if(action.type == Action::MOVE){
    //         if(Vec2::magnitude(dist) <= Vec2::magnitude(speed) * dt){
    //             speed = Vec2();
    //             associated.box.x = action.pos.x - associated.box.w / 2;
    //             associated.box.y = action.pos.y - associated.box.h / 2;
    //             taskQueue.pop();
    //         } else{
    //             speed = Vec2::normalize(dist) * 40;
    //             associated.box.x += speed.x * dt;
    //             associated.box.y += speed.y * dt;
    //         }
    //     } else if(action.type == Action::SHOOT){
    //         int index = rand() % minionArray.size();
    //         // std::cout << "minion: " << index << "\n";
    //         int cnt = 1;
    //         while(minionArray[index].expired() && cnt < minionArray.size()){
    //             index = (index + 1) % minionArray.size();
    //             cnt++;
    //         }
    //         if(!minionArray[index].expired()){
    //             auto *minion = dynamic_cast<Minion*>(minionArray[index].lock()->GetComponent(Minion::TYPE));
    //             minion->Shoot(action.pos);
    //         }
    //         taskQueue.pop();
    //     }
    // }
    if(hp <= 0){
        associated.RequestDelete();
        for(int i = 0; i < minionArray.size(); i++){
            if(!minionArray[i].expired()){
                auto *minion = dynamic_cast<Minion*>(minionArray[i].lock()->GetComponent(Minion::TYPE));
                minion->RequestDelete();

            }
        }
        associated.RequestDelete();

        GameObject *go = new GameObject();
        go->box = associated.box;
        Sprite *sprite = new Sprite(*go, "assets/img/aliendeath.png", 4, 0.14, 0.56);
        go->angleDeg = associated.angleDeg;
        go->AddComponent(sprite);

        Sound *sound = new Sound(*go, "assets/audio/boom.wav");
        sound->Play();
        go->AddComponent(sound);

        Game *game = Game::GetInstance();
        game->GetCurrentState().AddObject(go);
    }
}

void Alien::Render(){
    
}

bool Alien::Is(std::string type){
    return Alien::TYPE == type;
}

// Alien::Action::Action(ActionType type, float x, float y):
//   type(type),
//   pos(x, y){
    
// }


void Alien::NotifyCollision(GameObject& other){
    Bullet *bullet = dynamic_cast<Bullet*>(other.GetComponent(Bullet::TYPE));
    if(bullet != nullptr && !bullet->targetsPlayer){
        PerdeHP();
    }
}

void Alien::PerdeHP(){
    hp -= 10;
}