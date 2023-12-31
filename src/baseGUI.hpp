#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

namespace GUI{

    // Text alignment type
    enum ALIGNMENT_types{
        LEFT_text,
        MIDLE_text,
        RIGHT_text
    };

    // Static text on screen with drawing functions
    class staticText
    {
    private:
        TTF_Font* Font;
        SDL_Surface *Surface;
        SDL_Texture *Texture;
        SDL_Rect Rect;
        char *text;
        float posX;
        ALIGNMENT_types aligment;
        SDL_Color color;
    public:
        staticText(char* newText, const Uint8 size, const float newX, const float newY, const ALIGNMENT_types newAlignment = MIDLE_text, const SDL_Color newColor = WHITE);
        void updateText(LNG_types language);
        void updateText(LNG_types language, int number);
        void blit();
        ~staticText();
    };

    // Class of drawing dinamic text at screen
    class dinamicText
    {
    private:
        TTF_Font* Font;
        SDL_Surface *Surface;
        SDL_Texture *Texture;
        SDL_Rect Rect;
        int X;
    public:
        dinamicText(int size, int x, int y);
        void draw(std::string text, const ALIGNMENT_types alignment, SDL_Color color = BLACK);
        void clear();
    };

    class Slider{
    private:
        SDL_Texture *textureLine;
        SDL_Texture *textureButton;
        SDL_Rect destLine;
        SDL_Rect destButton;
    public:
        Slider(int y, IMG_names lineImage, IMG_names buttonImage);
        void blit(Uint8 state);
        bool in(int x, int y);
        int getX();
    };

    class Button
    {
    private:
        SDL_Texture *texture;
        SDL_Rect dest;
    public:
        Button(int x, int y, IMG_names textureIndex);
        void blit();
        bool in(int x, int y);
    };

    #if ANI_count
    class Animation
    {
    private:
        ANI_names type;
        SDL_Texture* texture;
        Uint32 frame;
        Uint64 prevTick;
        SDL_Rect dest;
    public:
        Animation( SDL_Rect destination, ANI_names newType );
        void blit();
        void clear();
    };
    #endif

    class Bar
    {
    private:
        SDL_Rect Back_rect;
        SDL_Rect Front_rect;
        SDL_Rect IconeRect;
        SDL_Texture* IconeTexture;
        SDL_Color color;
    public:
        Bar( const SDL_Rect dest, SDL_Color newColor, IMG_names icone );
        void blit( int width );
    };

    //void createAllHUD(const char* data);
}