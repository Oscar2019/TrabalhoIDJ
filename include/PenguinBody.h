#pragma once
#include <memory>
#include "Component.h"
#include "Geometry.h"
#include <string>

class PenguinBody : public Component {
    public:
        static const std::string TYPE;
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update (float dt);
        void Render ();
        bool Is (std::string type); 
        void NotifyCollision(GameObject& other);

        PenguinBody* player;
    private:
        std::weak_ptr< GameObject > pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
};
