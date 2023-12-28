
#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "init.hpp"
#include "dataLoader.hpp"
#include "baseGUI.hpp"
#include "pause.hpp"
#include "initFile.hpp"
#include "entity.hpp"

// Global structures
App app;              // Creating main varables

// Data for creating fonts
#if FNT_count
Uint8* fontMemory;  // Memory with font data
size_t fontSize;  // Size of memory buffer
#endif

// Global numbers
// Last time and previous ticks update
Uint64 oldMoveTime;
Uint64 oldDrawTime;
// Pause and init settings
LNG_types language;       // Switched languaged from language_types
Uint8 MusicVolume;    // Volume of music
Uint8 EffectsVolume;  // Volume of effects
Uint32 MaxScore;      // Max previous game score
Uint16 drawFPS;       // Max terget FPS to draw
Uint32 score;         // Game score

// Global variables
coord gridX;          // Game field width
coord gridY;          // Game field height 
Uint16 moveTime;      // Timer between snake moves
Uint16 length;        // Length of snake
Uint16 position;      // Position of sell, which updated
Uint8 fat;            // Flag of setting fat cell

// Global running flags
bool running = true;      // Main cycle game flag of running
bool game_over = true;    // Flag of ending the round
bool winning = false;     // Flag of showing winning text
bool loosing = false;     // Flag of showing loosing text
bool skipping = false;    // Flag of showing skipping text

//bool advertisingMode;  // Mode of showing 'advertisment'

// Texts variables and constants
// All textures
#if IMG_count
SDL_Texture* Textures[IMG_count];  // Array of all textures
#endif

// All animations
#if ANI_count
IMG_Animation* Animations[ANI_count];  // Array of all animations
#endif

// All music trcks
#if MUS_count
Mix_Music* Musics[MUS_count];      // Array of all music
#if ARCHIEVE_LOADING
SDL_RWops* MusicsData[MUS_count];  // Array of data for music
#endif
#endif

// All effects sounds
#if SND_count
Mix_Chunk* Sounds[SND_count];  // Array of all sound effects
#endif

SDL_Rect BACK_RECT;

// Global GUI
//GUI::fileText* texts;  // Global statick texts
GUI::staticText* texts[TXT_count];  // Global statick texts
//Animation Advertisment({0, GAME_HEIGHT, SCREEN_WIDTH, ADV_HIGHT}, ANIM_adv);
//Animation MenuAdvertisment({96, SCREEN_HEIGHT-192, 288, 192}, ANIM_menu);

// Initialasing dinamic structures
Head player;  // Player initialasing
std::vector<Tile> TileArray(START_WIDTH);
Fruit Apple;

// Main function
int main(int argv, char** args){
    initLibraries();  // Initialasing all need libraries
    loadInitFile();  // Load initialasing file file with settings
    createVideo();  // Creating video output system
    
    // Loading data from file
    loadData("data.dat");

    // Setting volumes of sounds
    Mix_VolumeMusic(MusicVolume);  // Setting volume of music
    Mix_Volume(-1, EffectsVolume);  // Setting volume of effects

    // Creating user interface
    setAllText();  // Setting all text
    updateTranslation(language);  // Updating text

    // Interface initialisation
    GUI::dinamicText scoreText(18, SCREEN_WIDTH/2, 10);
    GUI::Button esc(SCREEN_WIDTH - 24, 24, IMG_MENU_PAUSE);
    //if(!advertisingMode){}
    Mix_PlayMusic( Musics[MUS_main], -1 );  // Infinite playing music without advertisment
    
    /*Bar ShieldBar({20, 5, MAX_SHIELD, 10}, {0, 255, 0, 255}, IMG_shield);  // Shield/health bar
    Bar BoostBar({20, 20, 100, 10}, {0, 0, 255, 255}, IMG_bolt);  // Bar of the remaining boost time*/

    // Drawing first screen
    // Clearing screen before starting draw
    SDL_SetRenderDrawColor(app.renderer, BACKGROUND_COLOR);
    SDL_RenderClear(app.renderer);

    // Drawing game background
    for(int y=0; y < gridY; ++y)
        for(int x=0; x < gridX; ++x){
            SDL_Rect dest = {x * CELL_SIDE, y * CELL_SIDE + UP_MENU, CELL_SIDE, CELL_SIDE};
            SDL_RenderCopy(app.renderer, Textures[IMG_BACK_LIGHT + (x + y) % 2], NULL, &dest);
        }

    esc.blit();
    SDL_RenderPresent(app.renderer);

    // Cycle variables
    SDL_Event event;
    bool Shooting;

	while(running)  // Main game cycle
	{
        // Showing loading screen
        if(game_over){
            startMenu();
        }

        // Getting events
        while( SDL_PollEvent(&event) != 0 ){  
            switch (event.type){
            case SDL_QUIT:
                running = false;  // Exit from program
                break;

            case SDL_KEYDOWN:
                // Resseting field and next new generation
                player.setVector(event.key.keysym.sym);

                if (event.key.keysym.sym == SDLK_r){
                    game_over = true;
                    skipping = true;
                }
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    pause();
                }
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                if(esc.in(MouseX, MouseY)){  // Checking clicking on escape button
                    pause();
                }
            }
        }
        if(!running) break;  // Breaking main cycle, if necesary
        
        // Objects update
        if( ((SDL_GetTicks64() - oldMoveTime) > moveTime) ){  // Updating all objects once per need time
            // Moving objects if 
            player.move();  // Moving objects
            if(!loosing && !winning){
                position = (position + 1) % length;
                TileArray[position].end();
            }
            oldMoveTime = SDL_GetTicks64();
        }

        // Drawing all at screen
        if(SDL_GetTicks64() - oldDrawTime > 1000 / drawFPS){  // Checking, if drawing need
            // Drawing screen background
            SDL_SetRenderDrawColor(app.renderer, BACKGROUND_COLOR);
            SDL_RenderClear(app.renderer);

            // Drawing game background
            for(int y=0; y < gridY; ++y)
                for(int x=0; x < gridX; ++x){
                    SDL_Rect dest = {x * CELL_SIDE, y * CELL_SIDE + UP_MENU, CELL_SIDE, CELL_SIDE};
                    SDL_RenderCopy(app.renderer, Textures[IMG_BACK_LIGHT + (x+y) % 2], NULL, &dest);
                }

            // Drawing game sprites
            player.blit();  // Drawing player at screen
            Apple.blit();  // Drawing apple at screen
            for(int i = 0; i<length; ++i){
                TileArray[i].blit();  // Drawing all body at screen
            }

            // Drawing menu at screen
            esc.blit();
            scoreText.draw(std::to_string(score), GUI::MIDLE_text);

            // Blitting all objects on screen
            SDL_RenderPresent(app.renderer);  

            oldDrawTime = SDL_GetTicks64();  // Getting last update time
        };

        // Waiting until next moving or drawing
        Sint32 MoveSleep = ((SDL_GetTicks64() - oldMoveTime) - moveTime);
        Sint32 DrawSleep = ((SDL_GetTicks64() - oldDrawTime) - 1000/drawFPS);
        SDL_Delay( MAX(MIN( MoveSleep, DrawSleep ), 0) );
	}

    // Exiting program
    // Saving all data to setting file for next start
    saveInitFile();  
    
    // Clearing static texts
    clearAllText();

    // Clearing dynamic texts
    scoreText.clear();

    // Clearing animations
    /*if(advertisingMode){
        Advertisment.clear();
        MenuAdvertisment.clear();
    }*/

    // Cleaning all data
    unloadData();

    // Exiting
    deleteVideo();  // Destroying video output
    exitLibraries();  // Exiting all libraries
	return 0;
}