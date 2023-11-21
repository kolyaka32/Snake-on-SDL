#pragma once

#include "baseHud.hpp"
#include "structs.hpp"

// Types of language
enum{
    STANDART_LNG,        // Standart type of language (english)
    ENGLISH_LNG,         // English language
    RUSSIAN_LNG,         // Russian language
    RUSSIAN_IMPIRE_LNG,  // Russian impire meme language
    BELARUS_LNG          // Belarus meme language
} LANGUAGE_types;

// Setting text of interface
void setEnglishText();
void setRussianText();
void setImpireText();
void setBelarusText();

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
    TXT_WAIT_KEY,

    TXT_PAUSE_PAUSE,
    TXT_PAUSE_MUSIC,
    TXT_PAUSE_SOUND,

    TXT_count
};

// Declaring static text
extern staticText texts[TXT_count];

//extern Animation Advertisment;*/

// External values to save and load from settings file
extern Uint8 language;  // Language settings
extern Uint8 MusicVolume;  // Start volume of music
extern Uint8 EffectsVolume;  // Start volume of effects
extern Uint16 MaxScore;  // Maximal player score
extern Uint16 drawFPS;  // Setted frames per seconds

