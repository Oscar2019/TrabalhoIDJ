#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Geometry.h"
#include <string>

class Bullet : public Component{
    public:
        static const std::string TYPE;
        Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int qtdAnimation = 1, int animationSpeed = 0.15);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
        void NotifyCollision(GameObject& other);
        bool targetsPlayer;
    private:
        Vec2 speed; 
        float distanceLeft; 
        int damage; 
};
