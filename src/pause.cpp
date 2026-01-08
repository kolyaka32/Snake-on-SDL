/*
 * Copyright (C) 2023-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

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

void setAllText(){
    texts[TXT_MENU_NAME] = new GUI::staticText(
        "Snake on SDL!\0"
        "Змейка на SDL!\0"
        "Змѣйка на SDL!\0"
        "ШМУП бульба!"
        , 64, 0.5, 0.2);
    texts[TXT_MENU_KEYS] = new GUI::staticText(
        "Arrow or 'WASD' keys move\0"
        "Стрелочки или 'ЦВЫФ' для передвижения\0"
        "Benutzt du Pfeile auf der Tastatur oder 'WASD'\0"
        "Клавішы ca стрэлкамі перамяшчаюць к бульбу"
        , 22, 0.5, 0.3);
    texts[TXT_MENU_REST] = new GUI::staticText(
        "Press any key to begin\0"
        "Нажмите на любую кнопку для начала\0"
        "Drückst du beliebige Taste zum Start\0"
        "Націсніце любую бульба, каб пачаць бульба"
        , 18, 0.5, 0.35);
    texts[TXT_MENU_SCORE] = new GUI::staticText(
        "Your last score: %\0"
        "Ваш последний счёт: %\0"
        "Вашъ послѣдній счетъ: %\0"
        "Ваш апошні вынік бульба: %"
        , 20, 0.5, 0.5);
    texts[TXT_MENU_MAX_SCORE] = new GUI::staticText(
        "Your max score: %\0"
        "Ваш максимальный счёт: %\0"
        "Вашъ максимальный счетъ: %\0"
        "Ваш максімальны бульба: %"
        , 20, 0.5, 0.55);
    texts[TXT_WAIT_WIN] = new GUI::staticText(
        "You win!\0"
        "Вы выиграли!\0"
        "Вы выиграли!\0"
        "Ты выйграваеш бульба!"
        , 22, 0.5, 0.4);
    texts[TXT_WAIT_LOOSE] = new GUI::staticText(
        "You loose...\0"
        "Вы проиграли...\0"
        "Вы проиграли...\0"
        "Ты прайграў бульбу..."
        , 22, 0.5, 0.4);
    texts[TXT_WAIT_SKIP] = new GUI::staticText(
        "You stop game.\0"
        "Вы остановили игру.\0"
        "Вы остановили игру.\0"
        "Ты спыняеш гульню бульбу"
        , 22, 0.5, 0.4);
    texts[TXT_PAUSE_PAUSE] = new GUI::staticText(
        "Game on pause\0"
        "Игра на паузе\0"
        "Игра на паузѣ\0"
        "Ваша бульба на паўзе"
        , 30, 0.5, 0.03);
    texts[TXT_PAUSE_MUSIC] = new GUI::staticText(
        "Music:\0"
        "Музыка:\0"
        "Музыка:\0"
        "Гучнасць музыкі:"
        , 22, 0.5, 0.42);
    texts[TXT_PAUSE_SOUND] = new GUI::staticText(
        "Sounds:\0"
        "Звуки:\0"
        "Звуки:\0"
        "Гучнасць гукаў:"
        , 22, 0.5, 0.53);
}

void updateTranslation(LNG_types language){
    // Setting fruit skin
    switch (language)
    {
    case LNG_ENGLISH:
        SDL_SetWindowTitle(app.window, "Snake on SDL");
        Apple.setTexture(IMG_APPLE);
        break;

    case LNG_RUSSIAN:
        SDL_SetWindowTitle(app.window, "Змейка на SDL");
        Apple.setTexture(IMG_APPLE);
        break;

    case LNG_IMPIRE:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning", "Attention, this translation is only a joke and is not intended to offend anyone!", app.window);
        SDL_SetWindowTitle(app.window, "Змѣйка на SDL");
        Apple.setTexture(IMG_APPLE);
        break;

    case LNG_BELARUS:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning", "Attention, this translation is only a joke and is not intended to offend anyone!", app.window);
        SDL_SetWindowTitle(app.window, "Сімулятар злову бульбіны на SDL");
        Apple.setTexture(IMG_POTATO);
        break;
    }
    
    // Updating texts
    for(int i=0; i<TXT_count;++i){
        texts[i]->updateText(language);
    }
    // Updating dinamic texts
    texts[TXT_MENU_SCORE]->updateText(language, score);
    texts[TXT_MENU_MAX_SCORE]->updateText(language, MaxScore);
}

void clearAllText(){
    for(int i=0; i<TXT_count;++i){
        delete texts[i];
    }
}

// Pause menu
void pause(){
    // Creating pause interface
    GUI::Button esc(SCREEN_WIDTH - 24, 24, IMG_MENU_PAUSE);
    GUI::Slider MusicSlider(400, IMG_MENU_SCROLLER_LINE, IMG_MENU_SCROLLER_BUTTON);
    GUI::Slider SoundSlider(500, IMG_MENU_SCROLLER_LINE, IMG_MENU_SCROLLER_BUTTON);
    GUI::Button BtnFlagUSA(SCREEN_WIDTH/2 - 100, 140, IMG_FLAG_USA );
    GUI::Button BtnFlagRUS(SCREEN_WIDTH/2 + 100, 140, IMG_FLAG_RUS );
    GUI::Button BtnFlagIMP(SCREEN_WIDTH/2 - 100, 260, IMG_FLAG_RUS_IMP );
    GUI::Button BtnFlagBEL(SCREEN_WIDTH/2 + 100, 260, IMG_FLAG_BEL );

    // Pause cycle
    SDL_Event event;
    bool waiting = true;
    bool MouseDown = false;
    char inBox = NORMAL_BOX;
    LNG_types newLanguage = language;
    Uint64 prevSND = SDL_GetTicks64();

    // Starting loop for waiting for start
    while(waiting && running){  
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
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                MouseDown = true;
                break;

            case SDL_MOUSEBUTTONUP:
                MouseDown = false; 
                inBox = NORMAL_BOX;
                break;
            }
        }

        int MouseX, MouseY;
        SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
        if(MouseDown && inBox == NORMAL_BOX){
            if(esc.in(MouseX, MouseY)){
                waiting = false;
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
            if( SDL_GetTicks64() - prevSND > 200 ){
                Mix_PlayChannel(-1, Sounds[SND_eat], 0);
                prevSND = SDL_GetTicks64();
            }
            break;

        case ENGLISH_BOX:  // If touch english language box
            newLanguage = LNG_ENGLISH;
            break;

        case RUSSIAN_BOX:  // If touch russian language box
            newLanguage = LNG_RUSSIAN;
            break;

        case RUSSIAN_EMPIRE_BOX:  // If touch russian impire language box
            newLanguage = LNG_IMPIRE;
            break;

        case BELARUS_BOX:  // If touch belarus language box
            newLanguage = LNG_BELARUS;
            break;
        }

        // Checking for changing language
        if(newLanguage != language){
            language = newLanguage;
            updateTranslation(language);
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
        texts[TXT_PAUSE_PAUSE]->blit();
        texts[TXT_PAUSE_MUSIC]->blit();
        texts[TXT_PAUSE_SOUND]->blit();

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
    GUI::Button esc(SCREEN_WIDTH - 24, 24, IMG_MENU_PAUSE);

    // Resseting score
    if(score > MaxScore){
        MaxScore = score;
    }
    texts[TXT_MENU_SCORE]->updateText(language, score);
    texts[TXT_MENU_MAX_SCORE]->updateText(language, MaxScore);

    // Starting loop for waiting for start
    bool waiting = true;
    SDL_Event event;
    while(waiting && running){
        // Getting events
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                waiting = false;
                break;
                //return;
            
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

        // Drawing
        SDL_RenderClear(app.renderer);

        // Drawing game background
        for(int y=0; y < gridY; ++y)
            for(int x=0; x < gridX; ++x){
                SDL_Rect dest = {x * CELL_SIDE, y * CELL_SIDE + UP_MENU, CELL_SIDE, CELL_SIDE};
                SDL_RenderCopy(app.renderer, Textures[IMG_BACK_LIGHT + (x+y) % 2], NULL, &dest);
            }

        // Bliting HUD
        esc.blit();

        texts[TXT_MENU_NAME]->blit();
        texts[TXT_MENU_KEYS]->blit();
        texts[TXT_MENU_REST]->blit();
        texts[TXT_MENU_SCORE]->blit();
        texts[TXT_MENU_MAX_SCORE]->blit();

        // Extra texts of reason of stopping
        if(winning){
            texts[TXT_WAIT_WIN]->blit();
        }
        else if(loosing){
            texts[TXT_WAIT_LOOSE]->blit();
        }
        else if(skipping){
            texts[TXT_WAIT_SKIP]->blit();
        }
        SDL_RenderPresent(app.renderer);

        SDL_Delay(1000 / drawFPS);  // Extra delaying
    }
    //SDL_DestroyTexture(screen);
    // Resetting values
    winning = false;
    loosing = false;
    skipping = false;
    game_over = false;
}