#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "Error.h"

int main(int argc, char* args[]) {
	try{
		Game *game = Game::GetInstance();
		game->Run();
	} catch(EngineRuntimeError &e){
		std::cerr << e.what() << "\n";
	}

	return 0;
}