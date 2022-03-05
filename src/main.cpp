#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Error.h"
#include "Resources.h"

int main(int argc, char* args[]) {
	// std::cout << args[0] << "\n";
	std::srand(std::time(nullptr));
	try{
		Game *game = Game::GetInstance(); // Cria uma instância de um game
		game->Run(); // Roda o game
	} catch(EngineRuntimeError &e){
		std::cerr << e.what() << "\n"; // Se houver um erro o exiba
	}
	auto resources = Resources::GetInstance();
	resources.ClearImages();
	resources.ClearSounds();
	resources.ClearMusics();

	return 0;
}