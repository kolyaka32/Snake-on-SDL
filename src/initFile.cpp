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
    language = LNG_STANDART;
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
                language = LNG_RUSSIAN;
            }
            else if(lang == "english"){
                language = LNG_ENGLISH;
            }
            else if(lang == "russian empire"){
                language = LNG_IMPIRE;
            }
            else if(lang == "belarussian"){
                language = LNG_BELARUS;
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
            // Checking grid for getting over screen
            if(gridX > 60){
                gridX = 60;
            }
        }
        else if( first == "height" ){
            gridY = std::stoi( line.substr(line.rfind('=')+2) );
            // Checking grid for getting over screen
            if(gridY > 30){
                gridY = 30;
            }
        }
        else if( first == "move time" ){
            moveTime = std::stoi( line.substr(line.rfind('=')+2) );
        }
    }
    //
    BACK_RECT = {0, UP_MENU, gridX*CELL_SIDE, gridY*CELL_SIDE};  // Base background rect

    in.close();  // Closing reading file
}

void setInitData(){
    // Initialasing constant start text 
    setAllText();

    // Setting volumes of sounds
    Mix_VolumeMusic(MusicVolume);  // Setting volume of music
    Mix_Volume(-1, EffectsVolume);  // Setting volume of effects
}

// Saving initialasing file
void saveInitFile(){
    std::ofstream setting("settings.ini");  // Creating output file

    // Writing data to output
    switch (language)  // Writing language
    {
    case LNG_STANDART:
    case LNG_ENGLISH:
    default:
        setting << "language = english" << std::endl;
        break;
    case LNG_RUSSIAN:
        setting << "language = russian" << std::endl;
        break;
    case LNG_IMPIRE:
        setting << "language = russian empire" << std::endl;
        break;
    case LNG_BELARUS:
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