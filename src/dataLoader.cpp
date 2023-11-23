#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "zip.h"

#include "init.hpp"
#include "dataLoader.hpp"

// Arcieve local structs
static zip_t* archive;  // Archive with all data

// Counters of loaded files
static Uint8 loadedImages;
static Uint8 loadedAnimations;
static Uint8 loadedMusics;
static Uint8 loadedSounds;

// Function of open archive and setting base password
zip_t* openarchive(std::string archiveName){
    // Open archive with need name
    archive = zip_open(archiveName.std::string::c_str(), ZIP_RDONLY, NULL);

    #if PASSWORD
    zip_set_default_password(archive, PASSWORD);
    #endif

    // Returning archive for checking correction
    return archive;
};

// Function of getting data of archive file
static inline SDL_RWops* dataFromarchive(const char* name){
    // Openning need file
    zip_file_t* file = zip_fopen_encrypted(archive, name, 0, PASSWORD);
    
    zip_stat_t st;
	zip_stat(archive, name, 0, &st);  // Getting data of current file
    // Checking correction of file
    if(st.size == 0){  
        return NULL;
    }

    // Copping data to buffer
    char* buffer = (char*)malloc(sizeof(char*)*st.size);
    zip_fread(file, buffer, st.size);
    zip_fclose(file);
    // Creating SDL-based structure with data
    SDL_RWops* tempRW = SDL_RWFromMem(buffer, st.size);

    // Returning created data structure
    return tempRW;
};

// Functions of loading objects
// Function of loading game icone
static unsigned loadIcone(const char* name){
    // Getting icone data
    SDL_RWops* tempRW = dataFromarchive(name);

    // Setting window icone
    SDL_Surface* iconeImage = IMG_LoadICO_RW(tempRW);
    if(iconeImage == NULL){  // Checking creating image
        return 0;  // Returning 0 as error with loading
    }
    SDL_RWclose(tempRW);
    SDL_SetWindowIcon(app.window, iconeImage);
    SDL_FreeSurface(iconeImage);
    return ICO_count;  // Returning correction of loading
};

// Functions of loading selected image file
static void loadPicture(const char* name, IMG_names number){
    // Getting selected picture data
    SDL_RWops* tempRW = dataFromarchive(name);
    // Creating texture from data
    Textures[number] = SDL_CreateTextureFromSurface(app.renderer, IMG_LoadPNG_RW(tempRW));
    SDL_RWclose(tempRW);

    // Checking correction of loaded file
    if(Textures[number] != NULL){
        loadedImages++;
    };
};

// Function of loading selected GIF animation
static void loadAnimation(const char* name, ANI_names number){
    // Getting selected animation data
    SDL_RWops* tempRW = dataFromarchive(name);
    // Creating animation from data
    Animations[number] = IMG_LoadAnimation_RW(tempRW, 0);
    SDL_RWclose(tempRW);

    // Checking correction of loaded file
    if(Animations[number] != NULL){
        loadedAnimations++;
    };
};

// Function of loading selected music file
static void loadMusic(const char* name, MUS_names number){
    // Getting selected music track data
    SDL_RWops* tempRW = dataFromarchive(name);
    // Creating music track from data
    Musics[number] = Mix_LoadMUSType_RW(tempRW, MUS_MP3, 0);
    //Animations[number] = IMG_LoadAnimation_RW(tempRW, 1);
    SDL_RWclose(tempRW);

    // Checking correction of loaded file
    if(Musics[number] != NULL){
        loadedMusics++;
    };
};

// Function of loading selected sound
static void loadSound(const char* name, SND_names number){
    // Getting selected sound data
    SDL_RWops* tempRW = dataFromarchive(name);
    // Creating sound from data
    Sounds[number] = Mix_LoadWAV_RW(tempRW, 0);
    //Animations[number] = IMG_LoadAnimation_RW(tempRW, 1);
    SDL_RWclose(tempRW);

    // Checking correction of loaded file
    if(Sounds[number] != NULL){
        loadedSounds++;
    };
};

// Function of loading font
static unsigned loadFont(const char* name){
    // Openning font file
    zip_file_t* file = zip_fopen_encrypted(archive, name, 0, PASSWORD);
    
    zip_stat_t st;
	zip_stat(archive, name, 0, &st);  // Getting data from file
    // Checking correction of file
    if(st.size == 0){  
        return 0;
    }

    // Copping data to buffer
    fontMemory = (Uint8*)malloc(sizeof(Uint8*) * st.size);
    fontSize = st.size;
    zip_fread(file, fontMemory, st.size);
    zip_fclose(file);

    // Checking correction
    return FNT_count;
};

// Functions of loading objects from lists
// Loading all images
static unsigned loadAllImages(){
    loadedImages = 0;  // Resseting counter
    // Main menu structures
    loadPicture("img/esc_butt.png", IMG_MENU_PAUSE);
    loadPicture("img/shar_polzun.png", IMG_MENU_SCROLLER_BUTTON);
    loadPicture("img/Poloska_pod_polzunom.png", IMG_MENU_SCROLLER_LINE);
    // Flags in settings
    loadPicture("img/Flag_USA.png", IMG_FLAG_USA);
    loadPicture("img/Flag_RUS.png", IMG_FLAG_RUS);
    loadPicture("img/Flag_RUS_IMP.png", IMG_FLAG_RUS_IMP);
    loadPicture("img/Flag_BEL.png", IMG_FLAG_BEL);
    // Game background
    loadPicture("img/kletka_svet.png", IMG_BACK_LIGHT);
    loadPicture("img/kletka_tyma.png", IMG_BACK_DARK);
    // Game sprites
    // Eatable objects
    loadPicture("img/Apple.png", IMG_APPLE);
    loadPicture("img/Potato.png", IMG_POTATO);
    // Snake pictures
    loadPicture("img/Snake_head_turnL.png", IMG_HEAD_LEFT);
    loadPicture("img/Snake_Head1.png", IMG_HEAD_STRAIGHT);
    loadPicture("img/Snake_head_turnR.png", IMG_HEAD_RIGHT);
    loadPicture("img/Snake_TurningLeft.png", IMG_BODY_LEFT);
    loadPicture("img/Snake_torso.png", IMG_BODY_STRAIGHT);
    loadPicture("img/Snake_TurningRight.png", IMG_BODY_RIGHT);
    loadPicture("img/Snake_End.png", IMG_END);
    loadPicture("img/Snake_TurningLeft_fat.png", IMG_BODY_LEFT_FAT);
    loadPicture("img/Snake_Torso_fat.png", IMG_BODY_STRAIGHT_FAT);
    loadPicture("img/Snake_TurningRight_fat.png", IMG_BODY_RIGHT_FAT);
    loadPicture("img/Snake_End_fat.png", IMG_END_FAT);

    // Returning numbers of loaded files
    return loadedImages;
};

// Loading all animations
static unsigned loadAllAnimations(){
    loadedAnimations = 0;  // Resseting counter
    //loadAnimation("ani/.gif", ANI_);

    // Returning numbers of loaded files
    return loadedAnimations;
};

// Loading all music tracks
static unsigned loadAllMusic(){
    loadedMusics = 0;  // Resseting counter
    //loadMusic("mus/.mp3", MUS_);

    // Returning numbers of loaded files
    return loadedMusics;
};

// Loading all sounds
static unsigned loadAllSounds(){
    loadedSounds = 0;  // Resseting counter
    //loadSound("snd/.wav", SND_);

    // Returning numbers of loaded files
    return loadedSounds;
};

void loadData(std::string fileName){
    // Opening archive
    if(openarchive(fileName) == NULL){
        printf("Can't load arcieve");
        exit(ERR_FIL_OPN);
    }  

    // Loading data from archive
    if(loadIcone("img/Game.ico") != ICO_count){
        printf("Can't load game icone");
        exit(ERR_FIL_ICO);
    }
    if(loadAllImages() != IMG_count){
        printf("Wrong count of images");
        exit(ERR_FIL_IMG);
    }
    if(loadAllAnimations() != ANI_count){
        printf("Wrong count of animations");
        exit(ERR_FIL_ANI);
    }
    if(loadAllMusic() != MUS_count){
        printf("Wrong count of music");
        exit(ERR_FIL_MUS);
    }
    if(loadAllSounds() != SND_count){
        printf("Wrong count of sounds");
        exit(ERR_FIL_SND);
    }
    if(loadFont("fnt/Arial.ttf") != FNT_count){
        printf("Can't load font");
        exit(ERR_FIL_FNT);
    }

    // Closing archive
    zip_close(archive);
}

// Function of clearing all temporary data, loaded from arcieve
void unloadData(){
    // Unloading data in reverce form from loading

    // Deliting font data
    free(fontMemory);
    // Unloading sound effects
    for(int i=0; i < SND_count; ++i){
        Mix_FreeChunk(Sounds[i]);
    }
    // Unloading music effects
    for(int i=0; i < MUS_count; ++i){
        Mix_FreeMusic(Musics[i]);
    }
    // Unloading gif animations
    for(int i=0; i < ANI_count; ++i){
        IMG_FreeAnimation(Animations[i]);
    }
    // Unloading images
    for(int i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(Textures[i]);
        Textures[i] = NULL;
    }
};
