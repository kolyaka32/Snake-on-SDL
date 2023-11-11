#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

class dataLoader
{
private:
    SDL_RWops* dataFile;
    void expectCorrection();  // Function of expecting correction of numbers
    void loadIcone();  // Loading game icone
    void loadImage();  // Loading all images
    void createBack();  // Creating game background
    //void loadAnimation();  // Loading all GIF-animations
    //void loadMusic();  // Loading all music files
    //void loadAudio();  // Loading all audio effects
    void loadFont();  // Loading fonts 
public:
    void init(std::string name);  // Function of initialasing and loading data file
    void unload();
};

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
    IMG_BACK,
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
    IMG_count
};

// Names of music in array to use
enum MUS_names{
    //MUS_main,  // Main in-game song
    //MUS_menu,  // Menu waiting song
    // Final counter 
    MUS_count
};

// Names of sound effects in array to use
enum SND_names{
    /*SND_laser,  // Sound of shooting
    SND_bolt,  // Sound of power-up
    SND_shield,  // Sound of shield adding
    // Explosions
    SND_regExplosion,
    SND_sonicExplosion,*/
    // Final counter 
    SND_count
};

// Names of animations in array to use
enum ANI_names{
    /*ANI_menu,  // Menu animation of maxwell cat
    ANI_adv,  // In game advertisment (of watermellon)*/

    // Final counter
    ANI_count
};

#define SEPARATOR 0