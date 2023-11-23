#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "pause.hpp"

// Types of selected box
enum SELCTED_BOX_types{
    NORMAL_BOX,
    MUSIC_SLIDER_BOX,
    EFFECT_SLIDER_BOX,
    ENGLISH_BOX,
    RUSSIAN_BOX,
    RUSSIAN_EMPIRE_BOX,
    BELARUS_BOX
};

void setEnglishText(){
    texts[TXT_MENU_NAME].set("Snake on SDL!", 64, SCREEN_WIDTH/2, GAME_HEIGHT/5);
    texts[TXT_MENU_KEYS].set("Arrow or 'WASD' keys move", 22, SCREEN_WIDTH/2, GAME_HEIGHT*2/5);
    texts[TXT_MENU_REST].set("Press any key to begin", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+70);

    texts[TXT_MENU_SCORE].set("Your last score: " + std::to_string(score), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
    texts[TXT_MENU_MAX_SCORE].set("Your max score: " + std::to_string(MaxScore), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);

    texts[TXT_WAIT_WIN].set("You win!", 22, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+110);
    texts[TXT_WAIT_LOOSE].set("You loose...", 22, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+110);
    texts[TXT_WAIT_SKIP].set("You stop game.", 22, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+110);
    //texts[TXT_WAIT_KEY].set("Press any key to restart", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);

    texts[TXT_PAUSE_PAUSE].set("Game on pause", 30, SCREEN_WIDTH/2, 20);
    texts[TXT_PAUSE_MUSIC].set("Music:", 22, SCREEN_WIDTH/2, 360);
    texts[TXT_PAUSE_SOUND].set("Sounds:", 22, SCREEN_WIDTH/2, 460);

    SDL_SetWindowTitle(app.window, "Snake on SDL");

    // Changing game model back to apple
    Apple.setTexture(IMG_APPLE);
};

void setRussianText(){
    texts[TXT_MENU_NAME].set("Змейка на SDL!", 64, SCREEN_WIDTH/2, GAME_HEIGHT/5);
    texts[TXT_MENU_KEYS].set("Стрелочки или 'ЦВЫФ' для передвижения", 22, SCREEN_WIDTH/2, GAME_HEIGHT*2/5);
    texts[TXT_MENU_REST].set("Нажмите на любую кнопку для начала", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+70);

    texts[TXT_MENU_SCORE].set("Ваш последний счёт: " + std::to_string(score), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
    texts[TXT_MENU_MAX_SCORE].set("Ваш максимальный счёт: " + std::to_string(MaxScore), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);

    texts[TXT_WAIT_WIN].set("Вы выиграли!", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    texts[TXT_WAIT_LOOSE].set("Вы проиграли...", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    texts[TXT_WAIT_SKIP].set("Вы остановили игру.", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    //texts[TXT_WAIT_KEY].set("Нажмите на любую кнопку для старта", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);

    texts[TXT_PAUSE_PAUSE].set("Игра на паузе", 30, SCREEN_WIDTH/2, 20);
    texts[TXT_PAUSE_MUSIC].set("Музыка:", 22, SCREEN_WIDTH/2, 360);
    texts[TXT_PAUSE_SOUND].set("Звуки:", 22, SCREEN_WIDTH/2, 460);

    SDL_SetWindowTitle(app.window, "Snake on SDL");

    // Changing game model back to apple
    Apple.setTexture(IMG_APPLE);
};

void setImpireText(){
    // Important warning message
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning", "Attention, this translation is only a joke and is not intended to offend anyone!", app.window);

    texts[TXT_MENU_NAME].set("Змѣйка на SDL!", 64, SCREEN_WIDTH/2, GAME_HEIGHT/5);
    texts[TXT_MENU_KEYS].set("Стрѣлочки или '​ЦВЫФЪ​' для передвиженія", 22, SCREEN_WIDTH/2, GAME_HEIGHT*2/5);
    texts[TXT_MENU_REST].set("Нажмите на любую кнопку для начала", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+70);

    texts[TXT_MENU_SCORE].set("Вашъ послѣдній счетъ: " + std::to_string(score), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
    texts[TXT_MENU_MAX_SCORE].set("Вашъ максимальный счетъ: " + std::to_string(MaxScore), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);

    texts[TXT_WAIT_WIN].set("Вы выиграли!", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    texts[TXT_WAIT_LOOSE].set("Вы проиграли...", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    texts[TXT_WAIT_SKIP].set("Вы остановили игру.", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    //texts[TXT_WAIT_KEY].set("Нажмите на любую кнопку для старта", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    

    texts[TXT_PAUSE_PAUSE].set("Игра на паузѣ ", 30, SCREEN_WIDTH/2, 20);
    texts[TXT_PAUSE_MUSIC].set("Музыка", 22, SCREEN_WIDTH/2, 360);
    texts[TXT_PAUSE_SOUND].set("Звуки", 22, SCREEN_WIDTH/2, 460);

    SDL_SetWindowTitle(app.window, "Змѣйка на SDL");

    // Changing game model back to apple
    Apple.setTexture(IMG_APPLE);
};

void setBelarusText(){
    // Important warning message
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning", "Attention, this translation is only a joke and is not intended to offend anyone!", app.window);

    texts[TXT_MENU_NAME].set("ШМУП бульба!", 64, SCREEN_WIDTH/2, GAME_HEIGHT/5);
    texts[TXT_MENU_KEYS].set("Клавішы са стрэлкамі перамяшчаюць бульбу, прабел для стральбы па бульбе", 22, SCREEN_WIDTH/2, GAME_HEIGHT*2/5);
    texts[TXT_MENU_REST].set("Націсніце любую бульба, каб пачаць бульба", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+70);

    texts[TXT_MENU_SCORE].set("Ваш апошні вынік бульба: " + std::to_string(score), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
    texts[TXT_MENU_MAX_SCORE].set("Ваш максімальны бульба: " + std::to_string(MaxScore), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);

    texts[TXT_WAIT_WIN].set("Ты выйграваеш бульба!", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    texts[TXT_WAIT_LOOSE].set("Ты прайграў бульбу...", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    texts[TXT_WAIT_SKIP].set("Ты спыняеш гульню бульбу", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    //texts[TXT_WAIT_KEY].set("Націсніце любую клавішу, каб перазапусціць бульба", 18, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+110);
    
    texts[TXT_PAUSE_PAUSE].set("Ваша бульба на паўзе", 30, SCREEN_WIDTH/2, 20);
    texts[TXT_PAUSE_MUSIC].set("Гучнасць музыкі", 22, SCREEN_WIDTH/2, 360);
    texts[TXT_PAUSE_SOUND].set("Гучнасць гукаў", 22, SCREEN_WIDTH/2, 460);

    SDL_SetWindowTitle(app.window, "Сімулятар злову бульбіны на SDL");

    // Changing game model of apple to potato as joke
    Apple.setTexture(IMG_POTATO);
};

// Setting new numbers of score
static void setScore(){
    switch (language)
    {
    case STANDART_LNG:
    case ENGLISH_LNG:
        texts[TXT_MENU_SCORE].set("Your last score: " + std::to_string(score), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
        texts[TXT_MENU_MAX_SCORE].set("Your max score: " + std::to_string(MaxScore), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
        break;
    
    case RUSSIAN_LNG:
        texts[TXT_MENU_SCORE].set("Ваш последний счёт: " + std::to_string(score), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
        texts[TXT_MENU_MAX_SCORE].set("Ваш максимальный счёт: " + std::to_string(MaxScore), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
        break;

    case IMPIRE_LNG:
        texts[TXT_MENU_SCORE].set("Вашъ послѣдній счетъ: " + std::to_string(score), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
        texts[TXT_MENU_MAX_SCORE].set("Вашъ максимальный счетъ: " + std::to_string(MaxScore), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
        break;

    case BELARUS_LNG:
        texts[TXT_MENU_SCORE].set("Ваш апошні вынік бульба: " + std::to_string(score), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
        texts[TXT_MENU_MAX_SCORE].set("Ваш максімальны бульба: " + std::to_string(MaxScore), 20, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
    }
}

// Pause menu
void pause(){
    // Creating pause HUD
    Button esc(SCREEN_WIDTH - 24, 24, IMG_MENU_PAUSE);
    Slider MusicSlider(400, IMG_MENU_SCROLLER_LINE, IMG_MENU_SCROLLER_BUTTON);
    Slider SoundSlider(500, IMG_MENU_SCROLLER_LINE, IMG_MENU_SCROLLER_BUTTON);
    Button BtnFlagUSA(SCREEN_WIDTH/2 - 100, 140, IMG_FLAG_USA );
    Button BtnFlagRUS(SCREEN_WIDTH/2 + 100, 140, IMG_FLAG_RUS );
    Button BtnFlagIMP(SCREEN_WIDTH/2 - 100, 260, IMG_FLAG_RUS_IMP );
    Button BtnFlagBEL(SCREEN_WIDTH/2 + 100, 260, IMG_FLAG_BEL );

    // Pause cycle
    SDL_Event event;
    bool waiting = true;
    bool MouseDown = false;
    char inBox = NORMAL_BOX;
    //Uint64 prevSND = SDL_GetTicks64();
    while(waiting){  // Starting loop for waiting for start
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                waiting = false;
                return;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    waiting = false;  // Returning to game
                    return;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                MouseDown = true;
                break;

            case SDL_MOUSEBUTTONUP:
                MouseDown = false; 
                inBox = NORMAL_BOX;
            }
        }

        int MouseX, MouseY;
        SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
        if(MouseDown && inBox == NORMAL_BOX){
            if(esc.in(MouseX, MouseY)){
                waiting = false;
                return;
            }
            if(MusicSlider.in(MouseX, MouseY)){
                inBox = MUSIC_SLIDER_BOX;
            }
            else if(SoundSlider.in(MouseX, MouseY)){
                inBox = EFFECT_SLIDER_BOX;
            }
            else if(BtnFlagUSA.in(MouseX, MouseY)){
                inBox = ENGLISH_BOX;
            }
            else if(BtnFlagRUS.in(MouseX, MouseY)){
                inBox = RUSSIAN_BOX;
            }
            else if(BtnFlagIMP.in(MouseX, MouseY)){
                inBox = RUSSIAN_EMPIRE_BOX;
            }
            else if(BtnFlagBEL.in(MouseX, MouseY)){
                inBox = BELARUS_BOX;
            }
        };
        // Performing click on need box 
        switch(inBox)
        {
        case MUSIC_SLIDER_BOX:  // If touch music slider
            MusicVolume = (MouseX - MusicSlider.getX()) / 2;
            if(MouseX - MusicSlider.getX() < 0) MusicVolume = 0;
            if(MouseX - MusicSlider.getX() > 255) MusicVolume = 255;
            Mix_VolumeMusic(MusicVolume);  // Setting volume of music
            break;
        case EFFECT_SLIDER_BOX:  // If touch effects slider
            EffectsVolume = (MouseX - SoundSlider.getX()) / 2;
            if(MouseX - SoundSlider.getX() < 0) EffectsVolume = 0;
            if(MouseX - SoundSlider.getX() > 255) EffectsVolume = 255;
            Mix_Volume(-1, EffectsVolume);  // Setting volume of effects
            
            // Playing sound effect for understanding loud
            /*if( SDL_GetTicks64() - prevSND > 200 ){
                Mix_PlayChannel(-1, Sounds[SND_laser], 0);
                prevSND = SDL_GetTicks64();
            }*/
            break;
        case ENGLISH_BOX:  // If touch english language box
            if(language != ENGLISH_LNG){
                setEnglishText();
                language = ENGLISH_LNG;
            }
            break;
        case RUSSIAN_BOX:  // If touch russian language box
            if(language != RUSSIAN_LNG){
                setRussianText();
                language = RUSSIAN_LNG;
            }
            break;
        case RUSSIAN_EMPIRE_BOX:  // If touch russian impire language box
            if(language != IMPIRE_LNG){
                setImpireText();
                language = IMPIRE_LNG;
            }
            break;
        case BELARUS_BOX:  // If touch belarus language box
            if(language != BELARUS_LNG){
                setBelarusText();
                language = BELARUS_LNG;
            }
        }

        // Drawing  
        // Clearing screen before starting draw
        SDL_SetRenderDrawColor(app.renderer, BACKGROUND_COLOR);
        SDL_RenderClear(app.renderer);

        // Drawing game background
            for(int y=0; y < gridY; ++y)
                for(int x=0; x < gridX; ++x){
                    SDL_Rect dest = {x * CELL_SIDE, y * CELL_SIDE + UP_MENU, CELL_SIDE, CELL_SIDE};
                    SDL_RenderCopy(app.renderer, Textures[IMG_BACK_LIGHT + (x+y) % 2], NULL, &dest);
                }

        // Drawing menu
        // Showing extra text
        texts[TXT_PAUSE_PAUSE].draw();
        texts[TXT_PAUSE_MUSIC].draw();
        texts[TXT_PAUSE_SOUND].draw();

        // Drawing sliders
        MusicSlider.blit(MusicVolume*2);
        SoundSlider.blit(EffectsVolume*2);

        // Drawing buttons
        esc.blit();
        BtnFlagUSA.blit();
        BtnFlagRUS.blit();
        BtnFlagIMP.blit();
        BtnFlagBEL.blit();

        /*if(advertisingMode){
            Advertisment.blit();  // Drawing advertisment at bottom
        }*/
        SDL_RenderPresent(app.renderer);  // Blitting textures on screen
        SDL_Delay(1000 / drawFPS);  // Delaying time to decrease CPU loading
    }
};

// Menu, that show at start, winning or stopping
void startMenu(){
    // Adding HUD
    Button esc(SCREEN_WIDTH - 24, 24, IMG_MENU_PAUSE);

    // Resseting score
    if(score > MaxScore){
        MaxScore = score;
    }
    setScore();

    // Bliting new HUD
    esc.blit();

    texts[TXT_MENU_NAME].draw();
    texts[TXT_MENU_KEYS].draw();
    texts[TXT_MENU_REST].draw();
    texts[TXT_MENU_SCORE].draw();
    texts[TXT_MENU_MAX_SCORE].draw();

    // Extra texts of reason of stopping
    if(winning){
        texts[TXT_WAIT_WIN].draw();
    }
    else if(loosing){
        texts[TXT_WAIT_LOOSE].draw();
    }
    else if(skipping){
        texts[TXT_WAIT_SKIP].draw();
    }
    // Updating screen data
    SDL_RenderPresent(app.renderer);

    // Getting screenshot
    SDL_Surface* screenSur = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(app.renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenSur->pixels, screenSur->pitch);
    SDL_Texture* screen = SDL_CreateTextureFromSurface(app.renderer, screenSur);
    SDL_FreeSurface(screenSur);

    //SDL_SaveBMP(SDL_GetWindowSurface(app.window), "out.bmp");

    // Starting loop for waiting for start
    bool waiting = true;
    SDL_Event event;
    while(waiting){
        // Getting events
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                waiting = false;
                SDL_DestroyTexture(screen);
                return;
            
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    pause();
                }
                else{
                    player.reset();  // Resseting head position
                    length = START_WIDTH;
                    position = 0;
                    for(int i = 0; i < START_WIDTH; ++i){
                        player.move();  // Moving objects
                        position = (position + 1) % length;
                        TileArray[position].end();
                    }
                    Apple.set();
                    waiting = false;
                    score = 0;
                    break;
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
        // Checking, if stopping process need
        if(!running){
            SDL_DestroyTexture(screen);
            return;
        }
        if(!waiting) break; 

        // Drawing
        SDL_RenderCopy(app.renderer, screen, NULL, NULL);
        SDL_RenderPresent(app.renderer);

        SDL_Delay(1000 / drawFPS);  // Extra delaying
    }
    SDL_DestroyTexture(screen);
    // Resetting values
    winning = false;
    loosing = false;
    skipping = false;
    game_over = false;
}