#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define gridX 16
#define gridY 20
#define FPS 30

#define cellSide 32  // Width and height of mine
#define cycleTime 500  // Delta time of movement
#define StartWidth 5  // Starting width of snake

#define SCREEN_WIDTH gridX*cellSide
#define SCREEN_HEIGHT gridY*cellSide
#define maxLength gridX*gridY-3

// Names of directions and they numbers
enum direction{
    up,
    right,
    down,
    left
};

// Names of images in array to using
enum IMG_names{
    apple,
    background,
    head_left,
    head_straight,
    head_right,
    body_left,
    body_straight,
    body_right,
    fat_left,
    fat_straight,
    fat_right,
    body_end,
    IMG_count
};

// Names of files to load textures
std::string IMG_files[IMG_count]{
    "img/Apple.png",
    "img/Background.png",
    "img/Snake_head_turnL.png",
    "img/Snake_Head1.png",
    "img/Snake_head_turnR.png",
    "img/Snake_TurningLeft.png",
    "img/Snake_Torso.png",
    "img/Snake_TurningRight.png",
    "img/Snake_Left_fat.png",
    "img/Snake_Torso_fat.png",
    "img/Snake_Right_fat.png",
    "img/Snake_End.png"
};

struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
};

App app;  // Creating main varables

// Flags of running
bool running;  // Flag of main cycle work
bool loosing;  // Flag of showing loosing screen
bool winning;  // Flag of showing winning screen
bool gameStop;  // Flag of stoping game to loading screen without label

// Global numbers
int curTimer;  // Curient cycle time
int preTimer;  // Previous cycle time
int length;  // Length of snake
int position;  // Position of sell, which updated
int score;  // Number of eaten apples
int preTick; // Previous tick time
char fat;  // Flag of setting fat cell

// Texts variables and constants
TTF_Font* Font;
SDL_Texture *Textures[IMG_count];  // Array of all textures

// Functions
// Function of loading all textures to array
void loadTextures(){
    SDL_Surface *temp_surface;
    for(int i = 0; i < IMG_count; ++i){
        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", IMG_files[i]);
        temp_surface = IMG_Load(IMG_files[i].std::string::c_str());
        Textures[i] = SDL_CreateTextureFromSurface(app.renderer, temp_surface);
        SDL_FreeSurface(temp_surface);
    }
};

// Function clearing textures from RAM
void unloadTextures(){
    for(int i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(Textures[i]);
        Textures[i] = NULL;
    }
}

// Function of drawing text at screen
void drawText(std::string text, int x, int y){
    //static_assert(sizeof(wchar_t) == sizeof(Uint16));
    //TTF_RenderUNICODE_Blended(font, reinterpret_cast<Uint16 const *>(L"English текст"), color);
    SDL_Surface *textSurface = TTF_RenderText_Solid(Font, text.std::string::c_str(), {255, 255, 255});
    //SDL_Surface *textSurface = TTF_RenderUNICODE_Blended(Font, text, {255, 255, 255});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
    SDL_Rect textRect; textRect.x = x; textRect.y = y;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderCopy(app.renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

// Game classes
// Base entity in-game class
class Entity{
public:
    char x, y;
    SDL_Texture *texture;
    SDL_Rect dest;
//public:
    Entity(){};
    ~Entity(){};
    void init(char PosX, char PosY, IMG_names newTexture){
        x = PosX; y = PosY; //state = NewState;
        dest.x = PosX * cellSide;
        dest.y = PosY * cellSide;
        texture = Textures[newTexture];
    };
    void blit(){
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	    SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
    };
    int getPos(){
        return x+y*gridX;
    };
};

class Head:public Entity{
public:
    direction vec, newVec;
    void reset(){
        //char PosX, char PosY, IMG_names newTexture
        //gridX/2, gridY/2+StartWidth, head_straight
        init(gridX/2, gridY/2+StartWidth, head_straight);
        vec = up; newVec = up;
    };

    int move();
    
    void blit(){
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        if(vec == newVec){
            SDL_RenderCopyEx( app.renderer, Textures[head_straight], NULL, &dest, 360+vec*90, NULL, SDL_FLIP_NONE );
        }
        else if(newVec - vec  == -1 || newVec - vec == 3){
            SDL_RenderCopyEx( app.renderer, Textures[head_left], NULL, &dest, 270+vec*90, NULL, SDL_FLIP_NONE );
        }
        else if(newVec - vec == 1 || newVec - vec == -3){
            SDL_RenderCopyEx( app.renderer, Textures[head_right], NULL, &dest, 450+vec*90, NULL, SDL_FLIP_NONE );
        }
        
    };
};

Head player;  // Player initialasing

class Tile:public Entity{
public:
    direction vec;
public:
    void set(char PosX, char PosY, direction vector, direction newVector){
        x = PosX; y = PosY; vec = newVector;
        dest.x = PosX * cellSide;
        dest.y = PosY * cellSide;
        // Chosen need texture 
        if(vector - newVector == -1 || vector - newVector == 3){
            texture = Textures[body_right + fat*3];
        }
        else if(vector - newVector == 1 || vector - newVector == -3){
            texture = Textures[body_left + fat*3];
        }
        else{
            texture = Textures[body_straight + fat*3];
        }
    };

    void end(){
        texture = Textures[body_end];
    }

    void blit(){
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopyEx( app.renderer, texture, NULL, &dest, vec*90, NULL, SDL_FLIP_NONE );
    };
    
};

std::vector<Tile> TileArray(StartWidth);

class Fruit:public Entity{
public:
    void FindLocation(){
        bool in = true;;
        while(in){
            in = false;
            x = rand() % gridX;
            y = rand() % gridY;
            int Pos = y*gridX+x;
            for(int i=0; i< length; ++i){
                in = in || (TileArray[i].getPos() == Pos);
            }
            in = in || (Pos == player.getPos());
        }

        dest.x = x*cellSide;
        dest.y = y*cellSide;
    };
    void set(){
        FindLocation();
        init(x, y, apple);
    };
};

Fruit Apple;

int Head::move(){
    if(newVec == up){
        y-=1;
    }
    if(newVec == right){
        x+=1;
    }
    if(newVec == down){
        y+=1;
    }
    if(newVec == left){
        x-=1;
    }
    // Detecting exiting grid
    if(x < 0 || x >= gridX || y < 0 || y >= gridY){
        loosing = true;
        return -1;
    }
    // Detecting collision with snake
    int coord = y*gridX+x;
    for(int i=0; i< length; ++i){
        if(i != position && coord == TileArray[i].getPos()){
            loosing = true;
            return -2;
        }
    }
    // Detecting collision with apple
    if(y*gridX + x == Apple.getPos()){
        Apple.FindLocation();  // Getting new location of apple
        length += 1;  score += 10;
        Tile newTile;
        std::vector<Tile>::const_iterator iter = TileArray.cbegin() + position;
        TileArray.insert(iter, newTile);
        TileArray[position].set(dest.x / cellSide, dest.y / cellSide, vec, newVec);
        fat = 1;
        dest.x = x * cellSide; dest.y = y * cellSide;
        vec = newVec;
        if(length >= maxLength){
            winning = true;
        }
        return 2;
    }
    TileArray[position].set(dest.x / cellSide, dest.y / cellSide, vec, newVec);
    fat = 0;
    dest.x = x * cellSide; dest.y = y * cellSide;
    vec = newVec;
    return 1;
}

// Function of initialasing 
void initSDL()
{
    SDL_Init(SDL_INIT_VIDEO);  // Initialising SDL libarary

	app.window = SDL_CreateWindow("Try snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);  // Initialasing image library
    TTF_Init();  // Initialasing fonts library

    //setlocale(0, "russian");

    Font = TTF_OpenFont("Arial.ttf", 30);  // Reading font to drawing text

    // Resetting all variables
    running = true;
    loosing = false;
    winning = false;
    gameStop = true;
    score = 0;
    preTimer = 0;
    position = 0;
    length = StartWidth;
    fat = 0;
}

void cleanup(void)
{
    // Clearing all arrays
    TileArray.clear();

    // Closing all outside libraries
    TTF_CloseFont(Font);

	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	
	SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

// Main function
int main(int argv, char** args){
    initSDL();  // Initialasing of main SDL library
    loadTextures();  // Loading sprites to the game
    // Showing backround
    SDL_RenderCopy(app.renderer, Textures[background], NULL, NULL);  // Drawing background at screen
    SDL_RenderPresent(app.renderer);  // Blitting textures on screen

    SDL_Event event;
	while(running)  // Main game cycle
	{
        // Showing loading screen
        if(winning || loosing || gameStop){
            // Showing extra text
            if(winning){
                drawText("You win!", SCREEN_WIDTH/2 - 60, 15);
                //drawText("Вы выиграли!", SCREEN_WIDTH/2 - 60, 15);
            }
            else if(loosing){
                drawText("You lose!", SCREEN_WIDTH/2 - 60, 15);
                //drawText("Вы проиграли!", SCREEN_WIDTH/2 - 60, 15);
            }
            drawText( "Press 'r' to restart", SCREEN_WIDTH/2 - 120 , 60);
            //drawText( "Нажмите 'r' для рестарта", SCREEN_WIDTH/2 - 120 , 60);
            SDL_RenderPresent(app.renderer);

            // Starting loop for waiting for start
            bool waiting = true;
            while(waiting){
                while( SDL_PollEvent(&event) != 0 ){
                    if(event.type == SDL_QUIT){
                        running = false;  // Exit from program
                        waiting = false;
                    }
                    if (event.key.keysym.sym == SDLK_r) {
                        player.reset();  // Resseting head position
                        length = StartWidth;
                        position = 0;
                        for(int i = 0; i<StartWidth; ++i){
                            player.move();  // Moving objects
                            position = (position + 1) % length;
                            TileArray[position].end();
                        }
                        Apple.set();
                        waiting = false;
                        score = 0;
                    }
                }
                SDL_Delay(16);  // Extra delaying
            }
            SDL_RenderPresent(app.renderer);
            // Resetting values
            winning = false;
            loosing = false;
            gameStop = false;
        }

        while( SDL_PollEvent(&event) != 0 ){  // Getting events
            if(event.type == SDL_QUIT){
                running = false;  // Exit from program
            }
            if (event.type == SDL_KEYDOWN) {
                // Resseting field and next new generation
                if (event.key.keysym.sym == SDLK_w && player.vec != down){
                    player.newVec = up;
                }
                if (event.key.keysym.sym == SDLK_d && player.vec != left){
                    player.newVec = right;
                }
                if (event.key.keysym.sym == SDLK_s && player.vec != up){
                    player.newVec = down;
                }
                if (event.key.keysym.sym == SDLK_a && player.vec != right){
                    player.newVec = left;
                }
                if (event.key.keysym.sym == SDLK_r){
                    gameStop = true;
                }
            }
        }

        curTimer = SDL_GetTicks();  // Getting curent time

        if(curTimer - preTimer > cycleTime){  
            player.move();  // Moving objects
            if(!loosing && !winning){
                position = (position + 1) % length;
                preTimer = curTimer;  // Resetting timer
                TileArray[position].end();
            }
        }

        // Clearing screen
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
        SDL_RenderClear(app.renderer);

        // Drawing objects at screen
        SDL_RenderCopy(app.renderer, Textures[background], NULL, NULL);  // Drawing background at screen
        player.blit();  // Drawing player at screen
        Apple.blit();  // Drawing apple at screen
        for(int i = 0; i<length; ++i){
            TileArray[i].blit();  // Drawing body at screen
        }
        drawText( std::to_string(score), 20 , 15);  // Drawing text with score at screen
        
		SDL_Delay(1000/FPS);  // Delaying time to decrease CPU loading
	}
    // Exiting program and clearing all data
    unloadTextures();
    cleanup();
	return 0;
}