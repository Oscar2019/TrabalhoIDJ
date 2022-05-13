// #include "game_aux.h"
// #include "State.h"
// #include "InputManager.h"
// #include "Error.h"
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
// #include <stdio.h>

// Game *Game::instance = nullptr; // inicializa a instância com um ponteiro nulo

// // Cria uma instância de um game 
// Game::Game(std::string title, int width, int height) : 
//   window(nullptr), 
//   renderer(nullptr), 
//   state(nullptr),
//   frameStart(),
//   dt(),
//   width(width),
//   height(height){
//     int flags_mask = 0;
    
//     // Inicializa o vídeo, aúdio e timer do SDl
//     flags_mask = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER; 
//     if(SDL_Init(flags_mask) < 0){ // Se houver erro gera uma exceção
//         throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_Init: " + std::string(SDL_GetError()) + "\n");
//     }

//     // Inicializa o jpg, png e tif do SDl_IMG
//     flags_mask = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
//     if((IMG_Init(flags_mask) & flags_mask) != flags_mask){ // Se houver erro gera uma exceção
//         throw EngineRuntimeError_Line("[Game][Game(title, width, height)]IMG_Init: " + std::string(IMG_GetError()) + "\n");
//     }

//     // Inicializa o mod, mp3 e ogg do SDl_MIX
//     flags_mask = MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
//     if((Mix_Init(flags_mask) & flags_mask) != flags_mask){ // Se houver erro gera uma exceção
//         throw EngineRuntimeError_Line("[Game][Game(title, width, height)]Mix_Init: " + std::string(Mix_GetError()) + "\n");
//     }
    
//     if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
//         throw EngineRuntimeError_Line("[Game][Game(title, width, height)]Mix_OpenAudio: " + std::string(Mix_GetError()) + "\n");
//     }
//     Mix_AllocateChannels(32);

//     // Cria uma janela
//     window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
//     if(window == nullptr){ // Se houver erro gera uma exceção
//         throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_CreateWindow: " + std::string(SDL_GetError()) + "\n");
//     }

//     // Cria um rendere
//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if(renderer == nullptr){ // Se houver erro gera uma exceção
//         throw EngineRuntimeError_Line("[Game][Game(title, width, height)]SDL_CreateRenderer: " + std::string(SDL_GetError()) + "\n");
//     }

//     state = new State(); // Cria um novo estado do jogo

// }

// Game::~Game(){
//     SDL_DestroyRenderer(renderer); // destroy renderer
//     SDL_DestroyWindow(window); // destro a janela

//     Mix_CloseAudio(); 

//     Mix_Quit(); // fecha o SDL_MIX

//     IMG_Quit(); // fecha o SDL_IMG

//     SDL_Quit(); // fecha o SDL
// }

// // carrega o game
// void Game::Run(){
//     state->Start();
//     while(!state->QuitRequested()){ // enquanto o usuári não apertar para fechar
//         CalculaDeltaTime();
//         InputManager::GetInstance().Update();
//         state->Update(dt); // update o stado do jogo
//         state->Render(); // renderiza o estado dojogo
//         SDL_RenderPresent(renderer); 
//         SDL_Delay(33); // espera 33 ms
//     }
// }

// // retorna o renderer
// SDL_Renderer* Game::GetRenderer(){
//     return renderer;
// }

// // Retorna o estado do jogo
// State& Game::GetState(){
//     return *state;
// }

// // retora o singleton
// Game* Game::GetInstance(){
//     if(Game::instance == nullptr){
//         return Game::instance = new Game("Oscar|170112209", 1024, 600);
//     }
//     return Game::instance;
// }

// void Game::CalculaDeltaTime(){
//     int next_frameStart = SDL_GetTicks();
//     dt = (next_frameStart - frameStart) / 1000.0f;
//     frameStart = next_frameStart;
// }

// float Game::GetDeltaTime(){
//     return dt;
// }


// int Game::GetWidth(){
//     return width;
// }

// int Game::GetHeight(){
//     return height;
// }

