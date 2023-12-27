
#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"
#include "dataLoader.hpp"

#include "entity.hpp"

// Entity class
void Entity::init(char PosX, char PosY, IMG_names newTexture){
    x = PosX; y = PosY; 
    dest.x = PosX * CELL_SIDE;
    dest.y = PosY * CELL_SIDE + UP_MENU;
    texture = Textures[newTexture];
};

void Entity::blit(){
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
};

int Entity::getPos(){
    return x+y*gridX;
};


// Head (player) class
void Head::reset(){
    init(gridX/2, gridY/2 + START_WIDTH, IMG_HEAD_STRAIGHT);
    vec = UP; 
    newVec = UP;
};

void Head::setVector(SDL_Keycode key){
    if ((key == SDLK_w || key == SDLK_UP) && player.vec != DOWN){
        player.newVec = UP;
    }
    if ((key == SDLK_d || key == SDLK_LEFT) && player.vec != LEFT){
        player.newVec = RIGHT;
    }
    if ((key == SDLK_s || key == SDLK_DOWN) && player.vec != UP){
        player.newVec = DOWN;
    }
    if ((key == SDLK_a || key == SDLK_LEFT) && player.vec != RIGHT){
        player.newVec = LEFT;
    }
};

int Head::move(){
    switch (newVec)
    {
    case UP:
        y -= 1;
        break;
    case DOWN:
        y += 1;
        break;
    case LEFT:
        x -= 1;
        break;
    case RIGHT:
        x += 1;
        break;
    }
    // Detecting exiting grid
    if(x < 0 || x >= gridX || y < 0 || y >= gridY){
        game_over = true;
        loosing = true;
        return -1;
    }
    // Detecting collision with snake
    int coord = y*gridX+x;
    for(int i=0; i < length; ++i){
        if(i != position && coord == TileArray[i].getPos()){
            game_over = true;
            loosing = true;
            return -2;
        }
    }
    // Detecting collision with apple
    if(getPos() == Apple.getPos()){
        Apple.FindLocation();  // Getting new location of apple
        length++;
        score += ADD_SCORE;
        Tile newTile;
        std::vector<Tile>::const_iterator iter = TileArray.cbegin() + position;
        TileArray.insert(iter, newTile);
        TileArray[position].set(dest.x / CELL_SIDE, (dest.y - UP_MENU) / CELL_SIDE, vec, newVec);
        fat = 1;
        dest.x = x * CELL_SIDE; 
        dest.y = y * CELL_SIDE + UP_MENU;
        vec = newVec;
        if(length >= MAX_LENGTH){
            winning = true;
        }
        return 2;
    }
    TileArray[position].set(dest.x / CELL_SIDE, (dest.y - UP_MENU) / CELL_SIDE, vec, newVec);
    fat = 0;
    dest.x = x * CELL_SIDE; 
    dest.y = y * CELL_SIDE + UP_MENU;
    vec = newVec;
    return 1;
};

void Head::blit(){
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopyEx( app.renderer, Textures[IMG_HEAD_LEFT + (5 + newVec - vec) % 4], NULL, &dest,  newVec*90, NULL, SDL_FLIP_NONE );
};


// Tile class
void Tile::set(char PosX, char PosY, direction vector, direction newVector){
    x = PosX; 
    y = PosY; 
    vec = newVector;
    dest.x = PosX * CELL_SIDE;
    dest.y = PosY * CELL_SIDE + UP_MENU;

    // Chosen need texture 
    if(vector - newVector == -1 || vector - newVector == 3){
        type = (fat) ? (IMG_BODY_RIGHT_FAT) : (IMG_BODY_RIGHT);
    }
    else if(vector - newVector == 1 || vector - newVector == -3){
        type = (fat) ? (IMG_BODY_LEFT_FAT) : (IMG_BODY_LEFT);
    }
    else{
        type = (fat) ? (IMG_BODY_STRAIGHT_FAT) : (IMG_BODY_STRAIGHT);
    }
    texture = Textures[type];
};

void Tile::end(){
    texture = Textures[(type >= IMG_BODY_LEFT_FAT) ? (IMG_END_FAT) : (IMG_END)];
}

void Tile::blit(){
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopyEx( app.renderer, texture, NULL, &dest, vec*90, NULL, SDL_FLIP_NONE );
};


// Fruit class
void Fruit::FindLocation(){
    bool in = true;;
    while(in){
        in = false;
        x = rand() % gridX;
        y = rand() % gridY;
        int Pos = y*gridX+x;
        for(int i=0; i < length; ++i){
            in = in || (TileArray[i].getPos() == Pos);
        }
        in = in || (Pos == player.getPos());
    }

    dest.x = x*CELL_SIDE;
    dest.y = y*CELL_SIDE + UP_MENU;
};

void Fruit::set(){
    FindLocation();
    //init(x, y, IMG_APPLE);
    //texture = Textures[newTexture];
};

void Fruit::setTexture(IMG_names newTexture){
    texture = Textures[newTexture];
};
