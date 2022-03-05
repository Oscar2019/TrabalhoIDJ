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

        void Start();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component *cpt);
        void RemoveComponent(Component *cpt);
        Component* GetComponent(std::string type);
        void NotifyCollision(GameObject& other);

        Rect box;
    private:
        bool started;
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
    public:
        double angleDeg;
};
