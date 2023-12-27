#include "include.hpp"
#include <string.h>
#include "define.hpp"
#include "structs.hpp"
#include "dataLoader.hpp"
#include "baseGUI.hpp"
#include "pause.hpp"

using namespace GUI;

// Function of creating font with need height
static TTF_Font* createFont(int size){
    SDL_RWops* fontData = SDL_RWFromMem(fontMemory, fontSize);
    return TTF_OpenFontRW(fontData, 1, size);
};

// Class of static text
/*void staticText::clear(){
    SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
};

void staticText::set(std::string text, int size, int x, int y, ALIGNMENT_types alignment, SDL_Color color){
    Font = createFont(size);
    Surface = TTF_RenderUTF8_Solid(Font, text.std::string::c_str(), color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = x - Rect.w * alignment/2; Rect.y = y;
};

void staticText::draw(){
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};*/

// Static text imported from file
// Function of using previous command 
static inline void useCommand(Uint8 type, int* number, int temp){
    switch (type)
    {
    case 1:
        *number += temp;
        break;
    
    case 2:
        *number -= temp;
        break;

    case 3:
        *number *= temp;
        break;

    case 4:
        *number /= temp;
        break;
    }
    //*temp = 0;
};

//
static inline void parseNumber(int* number, const char* data, int* i){
    //
    int temp = 0;
    Uint8 type = 1;
    for(;data[*i] != ';'; ++(*i)){
        switch (data[*i])
        {
        // Constant numbers
        case 'W':
        case 'w':
            temp = SCREEN_WIDTH;
            break;

        case 'H':
        case 'h':
            temp = SCREEN_HEIGHT;
            break;

        /*case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            temp = 0;
            while(std::isdigit(data[*i++])){
                temp = temp * 10 + data[*i] - '0';
            }
            i--;
            break;*/

        case '+':
            useCommand(type, number, temp);
            type = 1;
            break;

        case '-':
            useCommand(type, number, temp);
            type = 2;
            break;

        case '*':
            useCommand(type, number, temp);
            type = 3;
            break;

        case '/':
            useCommand(type, number, temp);
            type = 4;
            break;
        }
        if(std::isdigit(data[*i])){
            temp = 0;
            while(std::isdigit(data[*i++])){
                temp = temp * 10 + data[*i] - '0';
            }
            i--;
        }
    }
    useCommand(type, number, temp);
}

//
static inline void parseText(std::string* texts, const char* data, int* i){
    Uint8 deep = 0;
    int textCounter = 0;
    for(; (data[*i] != ';' || deep > 0) && data[*i]; ++(*i)){
        switch (data[*i])
        {
        case '{':
        case '[':
            deep++;
            break;

        case '}':
        case ']':
            deep--;
            break;

        case '"':
        case '\'':
            int j=0;
            while(data[++*i] != '"' || data[*i] != '\'' || data[*i] ){
                texts[textCounter][j++] = data[*i];
            }
            texts[textCounter][j] = '\0';
            textCounter++;
            if(textCounter == LNG_count){
                return;
            }
            break;
        }
    }
}


fileText::fileText(const char* data){
    int size = 10;
    x = 0;
    int y = 0;
    aligment = MIDLE_text;

    // Reading all data string for getting all parametres
    for(int i=0; data[i] && data[i] != '}'; ++i){
        // Switching between parametres of text
        switch (data[i])
        {
        case 'S':
        case 's':
            // Size parameter
            parseNumber(&size, data, &i);
            break;

        case 'A':
        case 'a':
            // Aligment type (left, midle, right)
            for(; data[i] && data[i] != ';'; ++i){
                switch (data[i])
                {
                case 'L':
                case 'l':
                    aligment = LEFT_text;
                    break;
                
                case 'M':
                case 'm':
                    aligment = MIDLE_text;
                    break;

                case 'R':
                case 'r':
                    aligment = RIGHT_text;
                    break;
                }
            }
            break;

        case 'X':
        case 'x':
            // X position
            parseNumber(&x, data, &i);
            break;

        case 'Y':
        case 'y':
            // Y position
            parseNumber(&y, data, &i);
            break;

        case 'T':
        case 't':
            // Saving text
            parseText(texts, data, &i);
        }
    }

    // Creating text from get data
    Font = createFont(size);
    Dest.y = y;
};

fileText::fileText(int size, int newX, int newY, ALIGNMENT_types newAlignment, SDL_Color color){
    Font = createFont(size);
    Dest.y = newY;
    x = newX;
    aligment = newAlignment;
};

void fileText::setTranslate(LNG_types language){
    SDL_Surface* surface = TTF_RenderUTF8_Solid(Font, texts[language].std::string::c_str(), WHITE);
    Texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Dest.w, &Dest.h);
    Dest.x = x - Dest.w * aligment / 2; 
};

void fileText::blit(){
    SDL_RenderCopy(app.renderer, Texture, NULL, &Dest);
};

void fileText::clear(){
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

void createAllHUD(char* data){
    char* next = data;
    //texts = (fileText*)malloc(sizeof(fileText*) * TXT_count);

    realTXT_count = 0;
    while(((next = strstr(next, "TEXT")) != NULL) && realTXT_count < TXT_count){
        texts[realTXT_count++] = new fileText(next);
    }
};

void freeAllHUD(){
    for(int i=0; i<realTXT_count; ++i){
        free(texts[i]);
    }
}