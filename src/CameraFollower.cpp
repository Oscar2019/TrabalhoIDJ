#include "CameraFollower.h"
#include "State.h"
#include "StageState.h"
#include "Game.h"


const std::string CameraFollower::TYPE = "CameraFollower";

CameraFollower::CameraFollower(GameObject &go) :
  Component(go)
{
    
}

void CameraFollower::Update(float dt){
    StageState& state = dynamic_cast<StageState&>(Game::GetInstance()->GetCurrentState());
    associated.box.x = state.camera.pos.x;
    associated.box.y = state.camera.pos.y;
}

void CameraFollower::Render(){
    
}

bool CameraFollower::Is(std::string type){
    return type == CameraFollower::TYPE;
}

