//
// Created by gabriel on 19/01/18.
//

#ifndef MARIOLIKEV1_BUTTON_H
#define MARIOLIKEV1_BUTTON_H


#include <SDL_rect.h>
#include <SDL2/SDL_mixer.h>
#include "guiEntity.h"

class Button : public guiEntity{

public:
    const char* EntityName;
    Button(const char* name, int X, int Y, int W, int H);
    Button();


    virtual void listenEvents();

    virtual void Render(SDL_Renderer* rend);
    virtual const char* GetEntityName();
    virtual void SetEntityName(const char* newName);


    SDL_Texture* texture;

    virtual bool isPressed();
    virtual bool isOver();

    virtual void setTexture(SDL_Renderer* rend);
    virtual void setText(const char*, SDL_Renderer* _renderer);
private:
    Mix_Chunk *isOverSound;
    bool _ispressed, _isover;
    int x,y,h,w;
    SDL_Texture* messageTexture;
    SDL_Rect dest;
    SDL_Rect idle_source;
    SDL_Rect over_source;
    SDL_Rect textRect;
    SDL_Rect pressed_source;
    void _init();
    const char* _name;

};


#endif //MARIOLIKEV1_BUTTON_H
