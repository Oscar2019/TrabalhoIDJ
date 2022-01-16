#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Geometry.h"
#include <string>

class Bullet : public Component{
    public:
        static const std::string TYPE;
        Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
    private:
        Vec2 speed; 
        float distanceLeft; 
        int damage; 
};
