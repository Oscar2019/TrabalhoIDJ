#include "InputManager.h"
#include <SDL2/SDL.h>
#include <iostream>

void InputManager::Update(){
    quitRequested = false;
    if(SDL_QuitRequested() == SDL_TRUE){
        quitRequested = true;
    }
    SDL_Event event;

	SDL_GetMouseState(&mouseX, &mouseY);

    int time_frame = SDL_GetTicks();
    updateCounter = time_frame;
	while (SDL_PollEvent(&event)) {
        if(event.type == SDL_KEYDOWN){
            if(event.key.repeat == 1){
                continue;
            }
            int val{};
            if(event.key.keysym.sym <= 0x7F){
                val = event.key.keysym.sym;
            } else{
                val = event.key.keysym.sym - 0x3FFFFF81;
            }
            keyState[val] = true;
            keyUpdate[val] = time_frame;
            // keyUpdate[val] = event.key.timestamp;
            // updateCounter = event.key.timestamp;
        } else if(event.type == SDL_KEYUP){
            int val{};
            if(event.key.keysym.sym <= 0x7F){
                val = event.key.keysym.sym;
            } else{
                val = event.key.keysym.sym - 0x3FFFFF81;
            }
            keyState[val] = false;
            keyUpdate[val] = time_frame;
            // keyUpdate[val] = event.key.timestamp;
            // updateCounter = event.key.timestamp;
        } else if(event.type == SDL_MOUSEBUTTONDOWN){
            int val = event.button.button;
            mouseState[val] = true;
            keyUpdate[val] = time_frame;
            // mouseUpdate[val] = event.button.timestamp;
            // updateCounter = event.button.timestamp;
        } else if(event.type == SDL_MOUSEBUTTONUP){
            int val = event.button.button;
            mouseState[val] = false;
            keyUpdate[val] = time_frame;
            // mouseUpdate[val] = event.button.timestamp;
            // updateCounter = event.button.timestamp;
        } else if(event.type == SDL_QUIT){
            quitRequested = true;
        }
		
    }

    if(SDL_QuitRequested() == SDL_TRUE){
        quitRequested = true;
    }
}

bool InputManager::KeyPress(int key){
    int val{};
    if(key <= 0x7F){
        val = key;
    } else{
        val = key - 0x3FFFFF81;
    }
    return keyState[val] && keyUpdate[val] == updateCounter;
}

bool InputManager::KeyRelease(int key){
    int val{};
    if(key <= 0x7F){
        val = key;
    } else{
        val = key - 0x3FFFFF81;
    }
    return keyState[val] && keyUpdate[val] == updateCounter;
}

bool InputManager::IsKeyDown(int key){
    int val{};
    if(key <= 0x7F){
        val = key;
    } else{
        val = key - 0x3FFFFF81;
    }
    return keyState[val];
}

bool InputManager::MousePress(int button){
    int val{button};
    return mouseState[val] && mouseUpdate[val] == updateCounter;
}

bool InputManager::MouseRelease(int button){
    int val{button};
    return mouseState[val] && mouseUpdate[val] == updateCounter;
}

bool InputManager::IsMouseDown(int button){
    int val{button};
    return mouseState[val];
}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;
}

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}

InputManager::InputManager() :
    mouseState{},
    mouseUpdate{},    
    keyState{},
    keyUpdate{},
    quitRequested{},
    updateCounter{},
    mouseX{},
    mouseY{}
{

}

InputManager::~InputManager(){
    
}



