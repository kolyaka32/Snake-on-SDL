#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"


// Game classes
// Base entity in-game class
class Entity{
protected:
    Uint8 x, y;
    SDL_Texture *texture;
    SDL_Rect dest;
public:
    void init(char PosX, char PosY, IMG_names newTexture);
    void blit();
    int getPos();
};

// Head (player controlable part) of snake
class Head:public Entity{
    direction vec;
public:
    direction newVec;
    void reset();
    void setVector(SDL_Keycode key);
    int move();
    void blit();
};

// Normal (tile) part of snake or it end in different versions
class Tile:public Entity{
    direction vec;
    IMG_names type;
public:
    void set(char PosX, char PosY, direction vector, direction newVector);
    void end();
    void blit();
    
};

// Fruit class
class Fruit:public Entity{
public:
    void FindLocation();
    void set();
    void setTexture(IMG_names newTexture);
};
