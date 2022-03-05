#include "GameObject.h"
#include "Component.h"
#include <algorithm>
#include <iostream>

GameObject::GameObject() : 
  box{}, 
  started(false),
  components(), 
  isDead(false),
  angleDeg(0){
    
}

void GameObject::Start(){
    for(auto &component: components){
        component->Start();
    }
    started = true;
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Update(float dt){
    auto end = components.end();
    for(auto it = components.begin(); it != end; it++){
        auto &component = *it;
        component->Update(dt);
    }
}

void GameObject::Render(){
    auto end = components.end();
    for(auto it = components.begin(); it != end; it++){
        (*it)->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component *cpt){
    if(started){
        cpt->Start();
    }
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt){
    auto it = std::find_if(components.begin(), components.end(), [cpt](std::unique_ptr<Component> &c){
        return c.get() == cpt;
    });
    if(it != components.end()){
        components.erase(it);
    }
}

Component* GameObject::GetComponent(std::string type){
    auto is_same_type = [&type](std::unique_ptr<Component> &cpt){
        return cpt->Is(type);
    };
    auto it = std::find_if(components.begin(), components.end(), is_same_type);
    if(it != components.end()){
        return it->get();
    }
    return nullptr;
}

void GameObject::NotifyCollision(GameObject& other){
    auto end = components.end();
    for(auto it = components.begin(); it != end; it++){
        auto &component = *it;
        component->NotifyCollision(other);
    }
}

