// Base in-game global structs
#pragma once

#include "include.hpp"
#include "dataLoader.hpp"
#include "entity.hpp"

struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
};

struct FontData{
    char* fontMem;  // Memory with font data
    int size;  // Size of memory buffer
};

// Creating main varables
extern App app;  // Global main render and window
extern FontData fontData;  // Global data for creating fonts

// All in-game textures
extern SDL_Texture* Textures[IMG_count];  // Array of all textures

// All animations
/*extern IMG_Animation* Animations[ANIM_count];  // Array of all animations

// All music trcks
extern Mix_Music* Musics[MUS_count];  // Array of all music

// All effects sounds
extern Mix_Chunk* Sounds[SND_count];  // Array of all sound effects*/

// Flags of running
extern bool running;     // Flag of main cycle work
extern bool game_over;   // Flag of showing loosing screen
extern bool winning;     // Flag of showing winning text
extern bool loosing;     // Flag of showing loosing text
//extern bool advertisingMode;  // Mode of showing 'advertisment'

// Main glabal variables
extern Uint8 gridX;
extern Uint8 gridY;
extern Uint16 moveTime;
extern Uint16 length;    // Length of snake
extern Uint16 score;     // Number of eaten apples
extern Uint16 position;  // Position of sell, which updated
extern Uint16 preTick;   // Previous tick time
extern Uint8 fat;        // Flag of setting fat cell

// On screen entities
extern Head player;
extern std::vector<Tile> TileArray;
extern Fruit Apple;

extern SDL_Rect BACK_RECT;
