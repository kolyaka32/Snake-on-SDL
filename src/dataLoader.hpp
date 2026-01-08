/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

// Load file with all data
void loadData(std::string fileName);

// Function of clearing all temporary data, loaded from arcive
void unloadData();

// Archive values
#define PASSWORD NULL  // Archive password

// Used numerated numbers
#define ICO_count 1  // Number of icones for better count
#define FNT_count 1  // Number of fonts for better count

// Names of images in array to using
enum IMG_names{
    // Menu icones
    IMG_MENU_PAUSE,
    IMG_MENU_SCROLLER_BUTTON,
    IMG_MENU_SCROLLER_LINE,
    // Flags in settings
    IMG_FLAG_USA,
    IMG_FLAG_RUS,
    IMG_FLAG_RUS_IMP,
    IMG_FLAG_BEL,
    // Game background
    IMG_BACK_LIGHT,
    IMG_BACK_DARK,
    // Game sprites
    IMG_APPLE,
    IMG_POTATO,
    // Snake
    IMG_HEAD_LEFT,
    IMG_HEAD_STRAIGHT,
    IMG_HEAD_RIGHT,
    IMG_BODY_LEFT,
    IMG_BODY_STRAIGHT,
    IMG_BODY_RIGHT,
    IMG_END,
    IMG_BODY_LEFT_FAT,
    IMG_BODY_STRAIGHT_FAT,
    IMG_BODY_RIGHT_FAT,
    IMG_END_FAT,
};

#define IMG_count 22  // Counter of images

// Names of music in array to use
enum MUS_names{
    MUS_main,  // Main in-game song
    //MUS_menu  // Menu waiting song
};

#define MUS_count 1  // Music counter

// Names of sound effects in array to use
enum SND_names{
    SND_eat,  // Sound of eating
    SND_hit  // Sound of hitting in wall
};

#define SND_count 2  // Sounds counter

// Names of animations in array to use
enum ANI_names{
    /*ANI_menu,  // Menu animation of maxwell cat
    ANI_adv  // In game advertisment (of watermellon)*/
};

#define ANI_count 0  // Animations counter
