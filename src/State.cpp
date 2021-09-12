#include "State.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Face.h"

// Construtor default
State::State() : bg(* new GameObject()), music(), quitRequested(false){
    
}


State::~State(){
    objectArray.clear();
}

// retorna o valor da requisição de saída
bool State::QuitRequested(){
    return quitRequested;
}

// carrega os assts
void State::LoadAssets(){

    bg.Open("assets/img/ocean.jpg");
    music.Open("assets/audio/stageState.ogg");
    music.Play();
}

// atualiza o estado
void State::Update(float dt){
    Input();
    auto end = objectArray.end();
    
    for(auto it = objectArray.begin(); it != end; it++){
        auto &go = *it;
        go->Update(dt);
    }
    for(auto it = objectArray.begin(); it != end; ){
        auto &go = *it;
        if(go->IsDead()){
            it = objectArray.erase(it);
            end = objectArray.end();
        } else{
            it++;
        }
    }
}

// renderiza o estado
void State::Render(){
    bg.Render(0, 0);
    auto end = objectArray.end();
    for(auto it = objectArray.begin(); it != end; it++){
        auto &go = *it;
        go->Render();
    }
}


void State::Input(){
    if(SDL_QuitRequested() == SDL_TRUE){
        quitRequested = true;
    }
    SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(Rect::is_inside(go->box, {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent("Face");
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				// static int x00000000000000 = 0;
				Vec2 objPos = Vec2::rotate(Vec2( 200, 0 ), -PI + PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
				// Vec2 objPos = Vec2::rotate(Vec2( 200, 0 ),PI*(x00000000000000)/180.0) + Vec2(mouseX, mouseY);
				// x00000000000000++;
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY){
    GameObject *go = new GameObject();
    Sprite *sprite = new Sprite(*go,"assets/img/penguinface.png");
    Face *face = new Face(*go);
    go->box.x = mouseX;
    go->box.y = mouseY;
    go->box.w = sprite->getWidth();
    go->box.h = sprite->getHeight();
    go->AddComponent(sprite);
    go->AddComponent(face);
    objectArray.emplace_back(go);
}

