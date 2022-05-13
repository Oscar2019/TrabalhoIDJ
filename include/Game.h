#pragma once
#include <string>
#include <stack>
#include <memory>
#define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER 
// #define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"

class State;
class Game{
    private:
        Game(std::string title, int width, int height);
    public:
        ~Game();

        static Game* GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();
        
        void Push(State* state);
        
        void Run();
    private:
        void CalculaDeltaTime();
    public:
        float GetDeltaTime();
        int GetWidth();
        int GetHeight();

    private:
        static Game *instance;
        SDL_Window *window;
        SDL_Renderer *renderer;
        State *storedState;
        int frameStart;
        float dt;
        int width; 
        int height;
        std::stack<std::unique_ptr<State>> stateStack;
};
