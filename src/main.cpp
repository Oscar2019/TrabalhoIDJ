#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Error.h"

int main(int argc, char* args[]) {
	std::srand(std::time(nullptr));
	try{
		Game *game = Game::GetInstance(); // Cria uma instância de um game
		game->Run(); // Roda o game
	} catch(EngineRuntimeError &e){
		std::cerr << e.what() << "\n"; // Se houver um erro o exiba
	}

	return 0;
}