#pragma once
#include <string>
#include <SDL2/SDL.h>

class State;
class Game{
    private:
        Game(std::string title, int width, int height);
    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game* GetInstance();
    private:
        void CalculaDeltaTime();
    public:
        float GetDeltaTime();

    private:
        static Game *instance;
        SDL_Window *window;
        SDL_Renderer *renderer;
        State *state;
        int frameStart;
        float dt;
};
