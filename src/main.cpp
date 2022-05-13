#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Error.h"
#include "Resources.h"
#include "StageState.h"
#include "TitleState.h"
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER 
#define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"

int main(int argc, char* args[]) {
	// std::cout << args[0] << "\n";
	std::srand(std::time(nullptr));
	try{
		Game *game = Game::GetInstance(); // Cria uma instância de um game
		TitleState* titleState = new TitleState();
		// StageState* stageState = new StageState();
		game->Push(titleState);
		game->Run(); // Roda o game
	} catch(EngineRuntimeError &e){
		std::cerr << e.what() << "\n"; // Se houver um erro o exiba
	}

	return 0;
}