#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "initFile.hpp"
#include "pause.hpp"

// Loading initialasing settings in game
void loadInitFile(){
    // Reading file
    std::ifstream in("settings.ini"); // Open file to read
    std::string line;  // Output string line

    // Setting standart values for variables
    language = STANDART_LNG;
    MusicVolume = MIX_MAX_VOLUME/2;
    EffectsVolume = MIX_MAX_VOLUME/2;
    MaxScore = 0;
    drawFPS = 60;
    gridX = 16;
    gridY = 20;
    moveTime = 200;

    while(std::getline(in, line)){  // Reading file until it end
        std::string first = line.substr(0, line.find('=')-1);
        // Switching between options
        if( first == "language" ){
            std::string lang = line.substr(line.rfind('=')+2);
            if(lang == "russian"){
                language = RUSSIAN_LNG;
            }
            else if(lang == "english"){
                language = ENGLISH_LNG;
            }
            else if(lang == "russian empire"){
                language = RUSSIAN_IMPIRE_LNG;
            }
            else if(lang == "belarussian"){
                language = BELARUS_LNG;
            }
        }
        else if( first == "music" ){
            MusicVolume = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "effects" ){
            EffectsVolume = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "maxScore" ){
            MaxScore = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "FPS" ){
            drawFPS = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "width" ){
            gridX = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "height" ){
            gridY = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "move time" ){
            moveTime = std::stoi( line.substr(line.rfind('=')+2) );
        }
    }
    //
    BACK_RECT = {0, UP_MENU, gridX*CELL_SIDE, gridY*CELL_SIDE};  // Base background rect

    in.close();  // Closing reading file
}

// Creating game background
void createBackground(){
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

void setInitData(){
    // Initialasing constant start text 
    switch (language)  // Setting up language
    {
    case STANDART_LNG:  // English language
    case ENGLISH_LNG:
        setEnglishText();
        break;
    case RUSSIAN_LNG:  // Russian language
        setRussianText();
        break;
    case RUSSIAN_IMPIRE_LNG:  // Russian language
        setImpireText();
        break;
    case BELARUS_LNG:  // Russian language
        setBelarusText();
        break;
    }
    // Setting volumes of sounds
    Mix_VolumeMusic(MusicVolume);  // Setting volume of music
    Mix_Volume(-1, EffectsVolume);  // Setting volume of effects

    // Creating game background
    createBackground();
}

// Saving initialasing file
void saveInitFile(){
    std::ofstream setting("settings.ini");  // Creating output file

    // Writing data to output
    switch (language)  // Writing language
    {
    case STANDART_LNG:
    case ENGLISH_LNG:
    default:
        setting << "language = english" << std::endl;
        break;
    case RUSSIAN_LNG:
        setting << "language = russian" << std::endl;
        break;
    case RUSSIAN_IMPIRE_LNG:
        setting << "language = russian empire" << std::endl;
        break;
    case BELARUS_LNG:
        setting << "language = belarussian" << std::endl;
        break;
    }
    setting << "music = " << std::to_string(MusicVolume) << std::endl;  // Writing music volume
    setting << "effects = " << std::to_string(EffectsVolume) << std::endl;  // Writing effects volume
    setting << "maxScore = " << std::to_string(MaxScore) << std::endl;  // Writing max getting score
    setting << "FPS = " << std::to_string(drawFPS) << std::endl;  // Writing frames per seconds
    setting << "width = " << std::to_string(gridX) << std::endl;
    setting << "height = " << std::to_string(gridY) << std::endl;
    setting << "move time = " << std::to_string(moveTime) << std::endl;

    setting.close();  // Closing file
}