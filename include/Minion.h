#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Geometry.h"
#include <memory>
#include <string>

class Minion : public Component{
    public:
        static const std::string TYPE;
        Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
        void NotifyCollision(GameObject& other);
        void RequestDelete();
    private:
        std::weak_ptr<GameObject> alienCenter;
        float arc;
        float root;
        Vec2 myCenter;
};
