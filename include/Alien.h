#pragma once
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Geometry.h"
#include "Timer.h"
#include <queue>
#include <vector>
#include <memory>


class Alien : public Component{
    public:
        static const std::string TYPE;
        Alien(GameObject &associated, int nMinions);
        ~Alien();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void NotifyCollision(GameObject& other);
        void PerdeHP();
        static int alienCount;
    private:
        Vec2 speed; 
        int hp;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        enum AlienState : unsigned { MOVING = 0, RESTING = 1 };
        AlienState state;
        Timer restTimer;
        Vec2 destination;
};