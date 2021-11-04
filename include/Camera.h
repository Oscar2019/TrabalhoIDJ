#pragma once
#include "Geometry.h"

class GameObject;

class Camera{
    public:
        Camera();
        void Follow(GameObject* newFocus);
        void Unfollow();
        void Update(float dt);

        Vec2 pos;
        Vec2 speed;
    private:
        GameObject* focus;
};