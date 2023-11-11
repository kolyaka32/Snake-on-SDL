#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "init.hpp"
#include "dataLoader.hpp"

void dataLoader::expectCorrection(){
    if(dataFile == NULL){
        printf("Problems with loading data file.\n");
        exit(ERR_FIL_OPN);
    }
    if(SDL_ReadU8(dataFile) != SEPARATOR){
        printf("Problems with file separator.\n");
        exit(ERR_FIL_SEP);
    }
    if(SDL_ReadU8(dataFile) != GAME_VERSION){
        printf("Warning, that older version of data file than need.\n");
    }
    if(SDL_ReadU8(dataFile) != ICO_count){
        printf("Wrong count of icones.\n");
        exit(ERR_FIL_ICO);
    }
    if(SDL_ReadU8(dataFile) != IMG_count){
        printf("Wrong count of images.\n");
        exit(ERR_FIL_IMG);
    }
    if(SDL_ReadU8(dataFile) != ANI_count){
        printf("Wrong count of animations.\n");
        exit(ERR_FIL_ANI);
    }
    if(SDL_ReadU8(dataFile) != MUS_count){
        printf("Wrong count of music.\n");
        exit(ERR_FIL_MUS);
    }
    if(SDL_ReadU8(dataFile) != SND_count){
        printf("Wrong count of sounds.\n");
        exit(ERR_FIL_SND);
    }
    if(SDL_ReadU8(dataFile) != FNT_count){
        printf("Wrong count of fonts.\n");
        exit(ERR_FIL_FNT);
    }
    if(SDL_ReadU8(dataFile) != SEPARATOR){
        printf("Problems with file separator.\n");
        exit(ERR_FIL_SEP);
    }
};

void dataLoader::loadIcone(){
    Uint64 size = SDL_ReadLE32(dataFile);
    int* buf = (int*)malloc(size);
    SDL_RWread(dataFile, buf, size, 1);
    SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
    SDL_Surface* icone = IMG_LoadICO_RW(tempRW);
    if(icone == NULL){
        printf("Something wrong with icones.\n");
        exit(ERR_FIL_ICO);
    }
    SDL_SetWindowIcon(app.window, icone);
    SDL_FreeSurface(icone);
    SDL_RWclose(tempRW);
    free(buf);
};

void dataLoader::loadImage(){
    for(int i=0; i<IMG_count; ++i){
        Uint32 size = SDL_ReadLE32(dataFile);
        int* buf = (int*)malloc(size);
        SDL_RWread(dataFile, buf, size, 1);
        SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
        Textures[i] = SDL_CreateTextureFromSurface(app.renderer, IMG_LoadPNG_RW(tempRW));
        if(Textures[i] == NULL){
            printf("Something wrong with loading texture at %d.\n", i);
            exit(ERR_FIL_IMG);
        }
        SDL_RWclose(tempRW);
        free(buf);
    }
};

void dataLoader::createBack(){
    //renderTarget = SDL_GetRenderTarget(app.renderer);
    SDL_Texture* renderTarget = SDL_GetRenderTarget(app.renderer);

    Textures[IMG_BACK] = SDL_CreateTexture(app.renderer, 0, SDL_TEXTUREACCESS_TARGET, GAME_WIDTH, GAME_HEIGHT);
    SDL_SetTextureBlendMode(Textures[IMG_BACK], SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(app.renderer, Textures[IMG_BACK]);
    for(int y=0; y < gridY; ++y)
        for(int x=0; x < gridX; ++x){
            SDL_Rect dest = {x*CELL_SIDE, y*CELL_SIDE, CELL_SIDE, CELL_SIDE};
            SDL_RenderCopy(app.renderer, Textures[IMG_BACK_LIGHT + (x+y)%2], NULL, &dest);
        }
    //SDL_RenderCopy(app.renderer, Textures[IMG_BACK_DARK], NULL, NULL);
    SDL_SetTextureBlendMode(Textures[IMG_BACK], SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(app.renderer, renderTarget);
}

/*void dataLoader::loadAnimation(){
    for(int i=0; i<ANI_count; ++i){
        Uint64 size = SDL_ReadLE64(dataFile);
        int* buf = (int*)malloc(size);
        SDL_RWread(dataFile, buf, size, 1);
        SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
        Animations[i] = IMG_LoadGIFAnimation_RW(tempRW);
        SDL_RWclose(tempRW);
        free(buf);
    }
};*/

/*void dataLoader::loadAudio(){
    /*for(int i=0; i<MUS_count; ++i){
        Uint64 size = SDL_ReadLE64(dataFile);
        char* buf = (char*)malloc(size);
        SDL_RWread(dataFile, buf, size, 1);
        SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
        Musics[i] = Mix_LoadMUS_RW(tempRW, 1);
        free(buf);
        //Musics[i] = Mix_LoadMUSType_RW(tempRW, MUS_OGG, 0);
        
        //SDL_RWclose(tempRW);
        SDL_RWops* tempRW1 = SDL_RWFromFile("snd/mainTheme.ogg", "r");
        Musics[i] = Mix_LoadMUS_RW(tempRW1, 1);
    }
    SDL_RWops* tempRW1 = SDL_RWFromFile("mus/mainTheme.ogg", "r");
    Musics[MUS_main] = Mix_LoadMUSType_RW(tempRW1, MUS_OGG, 1);
    SDL_RWops* tempRW2 = SDL_RWFromFile("mus/menuTheme.ogg", "r");
    Musics[MUS_menu] = Mix_LoadMUSType_RW(tempRW2, MUS_OGG, 1);

    for(int i=0; i<SND_count;++i){
        Uint64 size = SDL_ReadLE64(dataFile);
        int* buf = (int*)malloc(size);
        SDL_RWread(dataFile, buf, size, 1);
        SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
        Sounds[i] = Mix_LoadWAV_RW(tempRW, 0);
        SDL_RWclose(tempRW);
        free(buf);
    }
};*/

void dataLoader::loadFont(){
    fontData.size = SDL_ReadLE32(dataFile);
    fontData.fontMem = (char*)malloc(fontData.size);
    if(SDL_RWread(dataFile, fontData.fontMem, fontData.size, 1) != 1){
        printf("Something wrong with loading font.\n");
        exit(ERR_FIL_FNT);
    }
};

void dataLoader::init(std::string name){
    dataFile = SDL_RWFromFile(name.std::string::c_str(), "r");
    expectCorrection();

    // Loading all data from file
    loadIcone();
    loadImage();
    //loadAnimation();
    //loadAudio();
    loadFont();

    // Closing file with data
    SDL_RWclose(dataFile);

    createBack();
};

void dataLoader::unload(){
    // Unloading data in reverce form from loading
    // Deliting font data
    free(fontData.fontMem);
    // Unloading sound effects
    /*for(int i=0; i < SND_count; ++i){
        Mix_FreeChunk(Sounds[i]);
    }
    // Unloading music effects
    for(int i=0; i < MUS_count; ++i){
        Mix_FreeMusic(Musics[i]);
    }
    // Unloading gif animations
    for(int i=0; i<ANIM_count;++i){
        IMG_FreeAnimation(Animations[i]);
    }*/
    // Unloading images
    for(int i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(Textures[i]);
        Textures[i] = NULL;
    }
};
