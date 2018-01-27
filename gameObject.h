//
// Created by gabriel on 23/01/18.
//

#ifndef MARIOLIKEV1_GAMEOBJECT_H
#define MARIOLIKEV1_GAMEOBJECT_H

#include <utility>
#include <iostream>
#include <SDL_system.h>

#include "GameEntity.h"

class gameObject : public GameEntity {
public:
    gameObject() = default;
    virtual void listenEvents() {};
    virtual void listenEvents(int* keyboardState){};
    virtual void setPos(int x, int y) {};
    virtual void setXpos(int x){};
    virtual void setYpos(int y){};
    virtual int getXPos() {};
    virtual int getYPos() {};
    virtual void Render() {};
    virtual void Render(SDL_Renderer * rend) {};
    virtual void loadTextures(SDL_Renderer* rend) {};
    virtual void loadTextures(){};

    virtual ~gameObject() override {
        std::cout<<"deleting game object\n";
    }
};


#endif //MARIOLIKEV1_GAMEOBJECT_H
