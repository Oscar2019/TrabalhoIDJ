#pragma once
#include "Component.h"
#include "GameObject.h"

class CameraFollower : public Component{
    public:
        static const std::string TYPE;
        CameraFollower(GameObject &go);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
};