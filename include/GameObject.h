#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Component.h"
#include "Geometry.h"

// class Component;

class GameObject{
    public:
        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component *cpt);
        void RemoveComponent(Component *cpt);
        Component* GetComponent(std::string type);

        Rect box;
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
};
