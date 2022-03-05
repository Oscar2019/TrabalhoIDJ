#pragma once
#include <string>
#include "Geometry.h"
#include "GameObject.h"
#include "Component.h"

class Collider : public Component{
    public:
        static const std::string TYPE;
        Collider ( GameObject& associated, Vec2 scale = {1, 1},  Vec2 offset = {0, 0});
        Rect box; 
        void Update (float dt);
        void Render();
        bool Is (std::string type);
        void SetScale (Vec2 scale);
        void SetOffset (Vec2 offset);
    private:
        Vec2 scale;
        Vec2 offset;
};