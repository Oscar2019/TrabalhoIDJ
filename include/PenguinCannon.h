#pragma once
#include <memory>
#include "Component.h"
#include "Geometry.h"
#include "Timer.h"
#include "GameObject.h"
#include <string>


class PenguinCannon : public Component {
    public:
        static const std::string TYPE;
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        ~PenguinCannon();

        void Update (float dt);
        void Render ();
        bool Is (std::string type); 
        
        void Shoot();
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        Timer timer;
};