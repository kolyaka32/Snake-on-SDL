#include "include.hpp"
#include <string.h>
#include "define.hpp"
#include "structs.hpp"
#include "dataLoader.hpp"
#include "baseGUI.hpp"
#include "pause.hpp"

using namespace GUI;

// Function of creating font with need height
static TTF_Font* createFont(Uint8 size){
    SDL_RWops* fontData = SDL_RWFromMem(fontMemory, fontSize);
    return TTF_OpenFontRW(fontData, 1, size);
};

staticText::staticText(char* newText, const Uint8 size, const float x, const float y, const ALIGNMENT_types newAligment, const SDL_Color newColor){
    Font = createFont(size);
    text = newText;
    posX = x;
    Rect.y = (SCREEN_HEIGHT) * y;
    aligment = newAligment;
    color = newColor;
};

void staticText::updateText(LNG_types language){
    Uint16 i = 0;
    for(Uint8 end = 0; (end != language); ++i){
        if(text[i] == '\0'){
            end++;
        }
    }
    
    Surface = TTF_RenderUTF8_Solid(Font, text + i, color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = (SCREEN_WIDTH) * posX - (Rect.w * aligment / 2); 
};

void staticText::updateText(LNG_types language, int number){
    char title[100];
    Uint8 start = 0;
    for(Uint8 end = 0; (end != language); ++start){
        if(text[start] == '\0'){
            end++;
        }
    }
    Uint8 d = 0;
    for(int i=start; text[i]; ++i ){
        if(text[i] == '%'){
            Uint8 end = 0;
            int num = number;
            do{
                num/=10;
                end++;
            } while(num);
            d += end;
            do {   
                title[--d] = '0' + number % 10;
                number /= 10;
            } while (number);
            d += end;
        }
        else{
            title[d++] = text[i];
        }
    }
    title[d] = '\0';
    
    Surface = TTF_RenderUTF8_Solid(Font, title, color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = (SCREEN_WIDTH) * posX - (Rect.w * aligment / 2); 
};

void staticText::blit(){
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};

staticText::~staticText(){
    SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
};


// Class of drawing dinamic text at screen
dinamicText::dinamicText(const int size, int x, int y){
    Font = createFont(size);
    X = x; Rect.y = y;
}

void dinamicText::clear(){
    TTF_CloseFont(Font);
    //SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
}

void dinamicText::draw(std::string text, const ALIGNMENT_types alignment, SDL_Color color){
    Surface = TTF_RenderText_Solid(Font, text.std::string::c_str(), color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = X - Rect.w * alignment/2;
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};


// Slider class
Slider::Slider(int y, IMG_names lineImage, IMG_names buttonImage){
    textureLine = Textures[lineImage];
    textureButton = Textures[buttonImage];
    SDL_QueryTexture(textureLine, NULL, NULL, &destLine.w, &destLine.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
    destLine.x = SCREEN_WIDTH/2-destLine.w/2; 
    destLine.y = y - destLine.h/2; 
    destButton.y = y - destButton.h/2;
};

void Slider::blit(Uint8 state){
    destButton.x = destLine.x + state - destButton.w/2;
    SDL_RenderCopy(app.renderer, textureLine, NULL, &destLine);
    SDL_RenderCopy(app.renderer, textureButton, NULL, &destButton);
};

bool Slider::in(int x, int y){
    return ((x > destLine.x && x < destLine.x+destLine.w) &&
        (y > destLine.y && y < destLine.y+destLine.h));
};

int Slider::getX(){
    return destLine.x;
};


// Button class
Button::Button(int x, int y, IMG_names textureIndex){
    texture = Textures[textureIndex];
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = x - dest.w/2; 
    dest.y = y - dest.h/2;
};

void Button::blit(){
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
};

bool Button::in(int x, int y){
    return ((x > dest.x && x < dest.x+dest.w) &&
        (y > dest.y && y < dest.y+dest.h));
};


#if ANI_count
// GIF animation class
Animation::Animation( SDL_Rect destination, ANI_names newType ){
    // Creating animation
    type = newType;
    dest = destination;
    frame = 0; 
    prevTick = 0;
};

void Animation::blit(){
    texture = SDL_CreateTextureFromSurface(app.renderer, Animations[type]->frames[frame]);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
    if(SDL_GetTicks64() > prevTick + Animations[type]->delays[0]){
        frame = (frame+1) % Animations[type]->count;
        prevTick = SDL_GetTicks64();
    }
};

void Animation::clear(){
    SDL_DestroyTexture(texture);
};
#endif


// Bar class
Bar::Bar( const SDL_Rect dest, SDL_Color newColor, IMG_names icone ){
    // Base bar
    Back_rect = dest;
    Front_rect = dest;
    color = newColor;
    // Icone part
    IconeTexture = Textures[icone];  // Texture of icone

    IconeRect = dest;
    IconeRect.w = 14;
    IconeRect.h = 16;
    IconeRect.y -= 2;
    IconeRect.x -= IconeRect.w + 2;
};

void Bar::blit( int width ){
    Front_rect.w = width;  // Setting width (health bar) 
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);  // Drawing back part
    SDL_RenderFillRect(app.renderer, &Back_rect);  
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);  // Drawing front part
    SDL_RenderFillRect(app.renderer, &Front_rect);
    SDL_RenderCopy(app.renderer, IconeTexture, NULL, &IconeRect);  // Rendering icone
};