#include "Text.h"
#include "GameObject.h"
#include "Error.h"
#include "Game.h"
#include "Resources.h"
#include <iostream>

const std::string Text::TYPE = "Text";

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color):
  Component(associated),
  font(nullptr),
  texture(nullptr),
  text(text),
  style(style),
  fontFile(fontFile),
  fontSize(fontSize),
  color(color){
	Resources& resources = Resources::GetInstance();
	font = resources.GetFont(fontFile, fontSize);
    RemakeTexture();
}

Text::~Text(){
    if(texture != nullptr){
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Text::Update(float dt){
    
}

void Text::Render(){
	Game *game = Game::GetInstance();
	SDL_Rect clipRect{
		0,
		0,
		static_cast<int>(associated.box.w),
		static_cast<int>(associated.box.h)
	}, destRect{
		static_cast<int>(associated.box.x), // Colocar camera
		static_cast<int>(associated.box.y), // Colocar Camera
		static_cast<int>(associated.box.w),
		static_cast<int>(associated.box.h)
	};
    if(SDL_RenderCopyEx(game->GetRenderer(), texture, &clipRect, &destRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) < 0){
        throw EngineRuntimeError_Line("[Text][Render()]SDL_RenderCopyEx: " + std::string(SDL_GetError()) + "\n");
    }
}

bool Text::Is(std::string type){
    return type == Text::TYPE;
}

void Text::SetText(std::string text){
    this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this->style = style;
	RemakeTexture();
}

void Text::SetFontFile(std::string fontFile){
    this->fontFile = fontFile;
	Resources& resources = Resources::GetInstance();
	font = resources.GetFont(fontFile, fontSize);
	RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this->fontSize = fontSize;
	Resources& resources = Resources::GetInstance();
	font = resources.GetFont(fontFile, fontSize);
	RemakeTexture();
}

void Text::RemakeTexture(){
    if(texture != nullptr){
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	SDL_Surface *surface;
	switch(style){
		case TextStyle::SOLID:{
			surface = TTF_RenderText_Solid(font, text.c_str(), color);
		}
		break;
		case TextStyle::SHADED:{
			surface = TTF_RenderText_Shaded(font, text.c_str(), color, SDL_Color{255,255,255,0});
		}
		break;
		case TextStyle::BLEND:{
			surface = TTF_RenderText_Blended(font, text.c_str(), color);
		}
		break;
		default:
		break;
	}
	Game *game = Game::GetInstance();
	texture = SDL_CreateTextureFromSurface(game->GetRenderer(), surface);
	associated.box.h = surface->h;
	associated.box.w = surface->w;
	SDL_FreeSurface(surface);
	
}


