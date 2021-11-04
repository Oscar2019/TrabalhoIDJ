#include "CameraFollower.h"
#include "State.h"
#include "Game.h"


const std::string CameraFollower::TYPE = "CameraFollower";

CameraFollower::CameraFollower(GameObject &go) :
  Component(go)
{
    
}

void CameraFollower::Update(float dt){
    associated.box.x = Game::GetInstance()->GetState().camera.pos.x;
    associated.box.y = Game::GetInstance()->GetState().camera.pos.y;
}

void CameraFollower::Render(){
    
}

bool CameraFollower::Is(std::string type){
    return type == CameraFollower::TYPE;
}

