#pragma once

// System numbers
#define WINDOWNAME "Snake on SDL"
#define GAME_WIDTH gridX * CELL_SIDE
#define GAME_HEIGHT gridY * CELL_SIDE
#define UP_MENU 100
#define DOWN_MENU 100
#define SCREEN_WIDTH GAME_WIDTH
#define SCREEN_HEIGHT GAME_HEIGHT + UP_MENU + DOWN_MENU

// Window and game base balance options
#define CELL_SIDE 32  // Width and height of mine
#define START_WIDTH 5  // Starting width of snake
#define MAX_LENGTH gridX*gridY-3
#define ADD_SCORE 10

// Base game colors
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}
#define BACKGROUND_COLOR 0, 150, 0, 255

// Names of directions and they numbers
enum direction{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// Macroses
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)