#include "Timer.h"


Timer::Timer() :
  time(){
    
}

void Timer::update(float dt){
    time += dt;
}

void Timer::Restart(){
    time = 0;
}

float Timer::Get(){
    return time;
}
