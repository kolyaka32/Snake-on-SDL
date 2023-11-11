#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"
#include "init.hpp"

App app;

SDL_RWops* outData;  // File with all in-game data
Uint8 gridX;
Uint8 gridY;

void loadFileRW(std::string name){
    // Opening need file
    SDL_RWops* temp = SDL_RWFromFile(name.std::string::c_str(), "r");

    int size = SDL_RWsize(temp);
    int* buf = (int*)malloc(size);  // Creating buffer area for data
    SDL_RWread(temp, buf, size, 1);
    SDL_WriteLE32(outData, size);
    SDL_RWwrite(outData, buf, size, 1);  // Writing that data to main data file
    SDL_RWclose(temp);
    free(buf);
}

// Main game function
int main(int argv, char** args){
    initLibraries();  // Initialasing all need libraries

    outData = SDL_RWFromFile("data.dat", "w");  // Output file

    // Writing data
    // Writing numbers to control correction
    SDL_WriteU8(outData, SEPARATOR);     // Writing seperator
    SDL_WriteU8(outData, GAME_VERSION);  // Writing version of created data file for extra correction
    SDL_WriteU8(outData, ICO_count);     // Writing number of icones
    SDL_WriteU8(outData, IMG_count);     // Writing number of images
    SDL_WriteU8(outData, ANI_count);     // Writing number of animations
    SDL_WriteU8(outData, MUS_count);     // Writing number of music tracks
    SDL_WriteU8(outData, SND_count);     // Writing number of audio effects
    SDL_WriteU8(outData, FNT_count);     // Writing number of fonts
    SDL_WriteU8(outData, SEPARATOR);     // Writing another separator

    
    // Loaing icone
    loadFileRW( "img/Game.ico");

    // Loading images
    loadFileRW( "img/esc_button.png");
    loadFileRW( "img/slider_button.png");  //IMG_MENU_SCROLLER_BUTTON,
    loadFileRW( "img/slider_line.png");  //IMG_MENU_SCROLLER_LINE,
    loadFileRW( "img/Flag_USA.png");
    loadFileRW( "img/Flag_RUS.png");
    loadFileRW( "img/Flag_RUS_IMP.png");
    loadFileRW( "img/Flag_BEL.png");

    loadFileRW( "img/kletka_svet.png");
    loadFileRW( "img/kletka_tyma.png");
    loadFileRW( "img/none.png");
    loadFileRW( "img/Apple.png");
    loadFileRW( "img/Potato.png");

    loadFileRW( "img/Snake_head_turnL.png");
    loadFileRW( "img/Snake_Head1.png");
    loadFileRW( "img/Snake_head_turnR.png");
    loadFileRW( "img/Snake_TurningLeft.png");
    loadFileRW( "img/Snake_torso.png");
    loadFileRW( "img/Snake_TurningRight.png");
    loadFileRW( "img/Snake_End.png");
    loadFileRW( "img/Snake_TurningLeft_fat.png");
    loadFileRW( "img/Snake_Torso_fat.png");
    loadFileRW( "img/Snake_TurningRight_fat.png");
    loadFileRW( "img/Snake_End_fat.png");

    // Loading gif animations
    //loadFileRW( "ani/");

    // Loading all music
    //loadFileRW( "mus/");

    // Loading all effects
    //loadFileRW( "snd/");

    loadFileRW( "fnt/Arial.ttf");

    SDL_RWclose(outData);  // Closing main file

    // Cleaning all data
    deleteVideo();

    return 0;
}
