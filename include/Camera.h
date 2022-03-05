#pragma once
#include "Geometry.h"
#include <map>

class GameObject;

class Camera{
    public:
        void Follow(GameObject* newFocus);
        void Unfollow();
        void Update(float dt);

        Vec2 pos;
        Vec2 speed;

        static std::map<int, Camera*> instances;
        static Camera& GetInstance(int instNum);
    private:
        Camera();
        GameObject* focus;
};