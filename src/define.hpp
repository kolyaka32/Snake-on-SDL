/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#define DEBUG false  // Debugging flag for testing
#define ARCHIEVE_LOADING !DEBUG  // Flag of loading data from archieve (or from folder)

// System numbers
#define WINDOWNAME "Snake on SDL"
#define GAME_WIDTH gridX * CELL_SIDE
#define GAME_HEIGHT gridY * CELL_SIDE
#define UP_MENU 50
#define DOWN_MENU 100
#define SCREEN_WIDTH GAME_WIDTH
#define SCREEN_HEIGHT GAME_HEIGHT + UP_MENU + DOWN_MENU

// Window and game base balance options
#define CELL_SIDE 32  // Width and height of mine
#define START_WIDTH 5  // Starting width of snake
#define MAX_LENGTH gridX * gridY - 3  // Length of snake to win
#define ADD_SCORE 10

// Base game colors
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}
#define BACKGROUND_COLOR 0, 150, 0, 255

// Types of language
enum LNG_types{
    LNG_ENGLISH,         // English language
    LNG_RUSSIAN,         // Russian language
    LNG_IMPIRE,          // Russian impire meme language
    LNG_BELARUS,         // Belarus meme language
};

#define LNG_count 4      // Final counter of all languages

// Types of data
typedef uint8_t coord;  // Type of data for coordinates
typedef uint16_t count;  // Type of data for mines counters

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