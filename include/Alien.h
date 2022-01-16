#pragma once
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Geometry.h"
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
    private:
        class Action{
            public:
                enum ActionType{
                    MOVE, 
                    SHOOT
                };
                Action(ActionType type, float x, float y);

                ActionType type;
                Vec2 pos;
        };
        Vec2 speed; 
        int hp;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;

};