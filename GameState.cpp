//
// Created by gabriel on 18/01/18.
//
#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <random>

#include "Player.h"
#include "GameState.h"
#include "Button.h"
#include "TextEntity.h"
#include "Camera.h"

Button ExitBut("Exit",175, 175, 30, 12);
Button PlayBut("Play!", 175, 100, 30, 12);
Button AnythingBut("Anything!", 175, 25, 30, 12);
Button HelpBut("Help!", 300, 300, 30, 12);
TextEntity text ("gabriel schneider", 0, 0, 200, 200);
Button BackBut("Back",window_W - 180, window_H - 80, 30, 12);

Player mainPlayer;
Camera camera(0, 0);

std::vector<std::vector<guiEntity*>> levelStages;
std::vector<std::vector<gameObject*>> gameStages;

Mix_Music* Music;
Mix_Chunk* isover;
//LevelManager::

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dist(0.0f, (float)window_W);


void InitMusic(){

    Mix_Init( MIX_INIT_MP3 | MIX_INIT_OGG );


    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());

    }

    //system("ls -la");
    Music = Mix_LoadMUS("money8bit.wav");
    if( Music == NULL ) {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    Mix_Volume(-1,MIX_MAX_VOLUME/3);
//    isover = Mix_LoadWAV("isOver.wav");
//    if(isover != NULL){
//        std::cout<<"HEYYYYYYY\n";
//    }
//    if(Mix_PlayMusic(Music, -1)==-1) {
//        printf("Mix_PlayMusic: %s\n", Mix_GetError());
//        // well, there's no music, but most games don't break without music...
//    }
}

void tickSeconds(int* fc, int8_t* status){

    while(*status) {
        *fc += 1;
//        std::cout << (*fc) << '\n';
        SDL_Delay(1);
    }
}

void HandleEvents(int8_t* status, SDL_Event* e, int* keystate){

    if(*status and status){
        std::cout<<"true\n";
    }

    while(*status) {
        while (SDL_PollEvent(e)) {
            SDL_GetMouseState(&mouseX, &mouseY);
            switch(e->type){
                case SDL_QUIT:
                    *status = false;
                    break;
                case SDL_KEYDOWN:
                    if(e->key.keysym.sym <= 150) {
                        std::cout << e->key.keysym.sym << " pressed \n";
                        keystate[e->key.keysym.sym] = true;
                    }
                    break;
                case SDL_KEYUP:
                    if(e->key.keysym.sym <= 150) {
                        std::cout << e->key.keysym.sym << " released\n";
                        keystate[e->key.keysym.sym] = false;
                    }

                case SDL_MOUSEBUTTONDOWN:
                    if(e->button.button == SDL_BUTTON_LEFT){
                        mouseButtonState[0] = true;
                    }
                    else{
                        mouseButtonState[1] = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseButtonState[0] = false;
                    mouseButtonState[1] = false;
                    break;
            }
        }
    }

    std::cout<<"exiting function\n";
}

void MainGameLoop(){
    int level = 0;

    levelStages.push_back({&PlayBut, &HelpBut, &AnythingBut, &ExitBut });
    levelStages.push_back({&text, &BackBut});
    levelStages.push_back({&BackBut});

    gameStages.push_back({});
    gameStages.push_back({});
    gameStages.push_back({&mainPlayer});

    for(size_t i = 0; i < levelStages.size(); i++) {
        for (guiEntity*obj : levelStages[i]){
            //gui Entities init functions
            obj->setText(obj->GetEntityName(), mainRenderer);
            obj->setTexture(mainRenderer);
        }

        for(gameObject* obj : gameStages[i]){
            //gameObjects init function
            obj->loadTextures(mainRenderer);

        }

    }

    while(isOpen) {
        RenderBackground();

        for(guiEntity* obj : levelStages[level] ){
            //std::cout<<obj->GetEntityName()<<'\n';
            obj->Render(mainRenderer);
            obj->listenEvents();

        }

        for(gameObject* obj : gameStages[level]){

           // int xoffset = obj->getXPos() - camera.x;
            //int yoffset = obj->getYPos() - camera.y;


            //obj->setXpos(xoffset);
            //obj->setYpos(yoffset);


            obj->listenEvents(keyboardState);
            obj->Render(mainRenderer);
        }

        camera.y -= 1;

        Render();

        SDL_Delay(10);

        for(size_t i = 0; i < (levelStages[level]).size(); i++){
            if( (levelStages[level])[i]->isPressed()){

                if((levelStages[level])[i]->GetEntityName() == "Play!"){
                        level = 2;
                }
                else if((levelStages[level])[i]->GetEntityName() == "Help!"){
                    SDL_Delay(100);
                    level++;
                }
                else if((levelStages[level])[i]->GetEntityName() == "Exit"){
                    SDL_Delay(100);
                    isOpen = false;
                }
                else if((levelStages[level])[i]->GetEntityName() == "Back"){
                    level--;
                    SDL_Delay(100);
                }


                else if((levelStages[level])[i]->GetEntityName() == "Anything!"){
                    Mix_PlayMusic(Music, -1);
                   (levelStages[level]).push_back(new Button("random", dist(mt), dist(mt) , 10, 10));
                    //Mix_PlayChannel(-1, isover, 0);
                    SDL_Delay(100);
                }

            }
        }

        if(keyboardState[SDLK_ESCAPE])
            isOpen = false;
    }
}

void RenderBackground(){
    SDL_RenderCopy(mainRenderer, backgroundText, NULL, NULL);

}

void setBackground(const char* name){
    SDL_Surface* temp = SDL_LoadBMP(name);
    backgroundText = SDL_CreateTextureFromSurface(mainRenderer, temp);
}

void RenderTexture(const char* name, SDL_Rect* srcRect, SDL_Rect* dstRect){
    SDL_Surface* temp = SDL_LoadBMP(name);
    SDL_Texture* text = SDL_CreateTextureFromSurface(mainRenderer, temp);
    SDL_RenderCopy(mainRenderer, text, srcRect, dstRect);
}

void Init() {

    InitMusic();

    window = SDL_CreateWindow("game", 100, 100, window_W, window_H, 0);
    mainRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    setBackground("defaultBG.bmp");
    isOpen = true;

    std::thread handle(HandleEvents, &isOpen, &event, keyboardState );
    std::thread countSeconds(tickSeconds, &mainFrameCount, &isOpen);

    MainGameLoop();

    std::cout << "has closed\n";

    handle.join();
    countSeconds.join();

    clearWindow();
}

void clearWindow() {
    Mix_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(mainRenderer);
    SDL_Quit();
}

void Render() {
//    SDL_SetRenderDrawColor( mainRenderer,
//                            mainFrameCount % 255,
//                            mainFrameCount % 100,
//                            mainFrameCount % 230,
//                            10 );

//    SDL_RenderClear(mainRenderer);

    SDL_RenderPresent(mainRenderer);
}



unsigned int getTicks(){
    return mainFrameCount;
}

int getMouseXPos(){
    return mouseX;
}

int getMouseYPos(){
    return mouseY;
}
int getMouseLeft(){
    return mouseButtonState[0];
}
int getMouseRight(){
    return mouseButtonState[1];
}

SDL_Renderer *getRenderer() {
    return mainRenderer;
}
