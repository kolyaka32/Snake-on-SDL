#pragma once

#include "baseGUI.hpp"
#include "structs.hpp"

// Working with text
// Functions for setting text at his place and his text
void setAllText();  
// Function of updating translation of all texts
void updateTranslation(LNG_types language);
// Function of clearing text SELCTED_BOX_types
void clearAllText();

// Pause menu with settings
void pause();

// First loaded menu and game start waiting screen
void startMenu();

// types of numerated texts
enum TXT_types{
    TXT_MENU_NAME,
    TXT_MENU_KEYS,
    TXT_MENU_REST,

    TXT_MENU_SCORE,
    TXT_MENU_MAX_SCORE,

    TXT_WAIT_WIN,
    TXT_WAIT_LOOSE,
    TXT_WAIT_SKIP,

    TXT_PAUSE_PAUSE,
    TXT_PAUSE_MUSIC,
    TXT_PAUSE_SOUND
};
#define TXT_count 11  // Final counter of all texts

// Declaring static text
extern GUI::staticText* texts[TXT_count];

// Declaring global list of animations
#if ANI_count
extern Animation Advertisment[ANI_count];
#endif

// External values to save and load from settings file
extern LNG_types language;  // Language settings
extern Uint8 MusicVolume;  // Start volume of music
extern Uint8 EffectsVolume;  // Start volume of effects
extern Uint32 MaxScore;  // Maximal player score
extern Uint16 drawFPS;  // Setted frames per seconds
