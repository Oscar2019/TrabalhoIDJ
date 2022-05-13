#pragma once
#include "Component.h"
#include "GameObject.h"
#include <string>
#define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER 
#define INCLUDE_SDL_TTF 
// #define INCLUDE_SDL_NET 
#include "SDL_include.h"

enum class TextStyle{
    SOLID,
    SHADED,
    BLEND,
};

class Text: public Component{
    public:
        static const std::string TYPE;
        Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
        ~Text();
        
        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void SetText(std::string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(std::string fontFile);
        void SetFontSize(int fontSize);
    private:
        void RemakeTexture();
        TTF_Font* font;
        SDL_Texture* texture;
        std::string text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color;
};


