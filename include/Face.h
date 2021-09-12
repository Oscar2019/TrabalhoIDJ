#pragma once

#include "Component.h"

class Face: public Component{
    public:
        static const std::string TYPE;
        Face(GameObject &associated);

        void Damage(int damage);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
    
    private:
        int hitpoints;
};
