//
// Created by gabriel on 20/01/18.
//

#ifndef MARIOLIKEV1_GUIENTITY_H
#define MARIOLIKEV1_GUIENTITY_H

#include <iostream>
#include <SDL2/SDL.h>
#include "GameEntity.h"

class guiEntity : public GameEntity {
public:
    guiEntity() = default;

    virtual void Render(SDL_Renderer* rend){};
    virtual const char* GetEntityName(){};
    virtual void SetEntityName(const char* newName){};

    virtual bool isPressed(){};
    virtual bool isOver(){};

    virtual void setTexture(SDL_Renderer* rend){};
    virtual void setText(const char*, SDL_Renderer* _renderer){};
    virtual void listenEvents(){return;};



};


#endif //MARIOLIKEV1_GUIENTITY_H
