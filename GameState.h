//
// Created by gabriel on 18/01/18.
//

#ifndef MARIOLIKEV1_GAMESTATE_H
#define MARIOLIKEV1_GAMESTATE_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>

static int window_W = 500;
static int window_H = 500;

static int mouseButtonState[2];
static int mouseX,mouseY;
static SDL_Event event;

static SDL_Renderer* mainRenderer;
static SDL_Texture* backgroundText;

static int8_t isOpen;

static int keyboardState[150];

static int mainFrameCount = 0;

static SDL_Window* window;

int getMouseXPos();
int getMouseYPos();
int getMouseLeft();
int getMouseRight();
SDL_Renderer* getRenderer();

void setBackground(const char* name);
void initFlags();
void HandleEvents(int8_t* status, SDL_Event* e, int* keystate);
void MainGameLoop();
void RenderBackground();
void RenderTexture(const char* name, SDL_Rect* srcRect, SDL_Rect* dstRect);
void Init();
void Render();
void clearWindow();
void tick();
unsigned int getTicks();



#endif //MARIOLIKEV1_GAMESTATE_H

