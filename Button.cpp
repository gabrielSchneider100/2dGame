//
// Created by gabriel on 19/01/18.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>

#include "Button.h"
#include "GameState.h"


Button::Button( const char* name, int X, int Y, int W, int H): x(X), y(Y), w(W), h(H), _name(name) {
    EntityName = name;
    _init();

    setTexture(getRenderer());
    setText(EntityName, getRenderer());

}

Button::Button() {
    _init();
}

bool Button::isPressed() {
   return _ispressed;
}

bool Button::isOver() {
   return _isover;
}


void Button::Render(SDL_Renderer* rend) {
    rend = getRenderer();
   // std::cout<<"rendering buton\n";
    if(isPressed()) {
        SDL_RenderCopy(rend, texture, &pressed_source, &dest);
    }

    else if(isOver() and !isPressed())
        SDL_RenderCopy(rend, texture, &over_source, &dest);
    else
        SDL_RenderCopy(rend, texture, &idle_source, &dest);

    SDL_RenderCopy(rend, messageTexture, NULL, &dest);
}

void Button::_init() {
    dest.x = x;
    dest.y = y;
    dest.w = w * 5;
    dest.h = h * 5;

    idle_source.x = 0;
    idle_source.y = 0;
    idle_source.w = 30;
    idle_source.h = 12;

    pressed_source.x = 50;
    pressed_source.y = 0;
    pressed_source.w = 30;
    pressed_source.h = 12;

    over_source.x = 0;
    over_source.y = 13;
    over_source.w = 30;
    over_source.h = 12;



}

void Button::setTexture(SDL_Renderer* rend) {

    rend = getRenderer();

    SDL_Surface* temmp = SDL_LoadBMP("gui.bmp");

    if(temmp != NULL)
        std::cout<<"creating button texcture\n";

    setText(_name, rend);
    texture = SDL_CreateTextureFromSurface(rend, temmp);
    isOverSound = Mix_LoadWAV("isOver.wav");
}

void Button::setText(const char* text, SDL_Renderer* _renderer) {

    _renderer = getRenderer();

    if(TTF_Init()<0){
        std::cout<<"error text texture: "<<TTF_GetError() <<'\n';
    }

    else {
        TTF_Font *Sans = TTF_OpenFont("Raleway.ttf", 24);

        if (Sans != NULL) {

            SDL_Color White = {255, 255, 255};
            SDL_Surface *messase = TTF_RenderText_Solid(Sans, text, White);
            messageTexture = SDL_CreateTextureFromSurface(_renderer, messase);

            std::cout << "text created!\n";
        } else {
            std::cout << "error text texture: " << TTF_GetError() << '\n';

        }
    }




}

void Button::listenEvents() {
    if( (getMouseXPos() > x and getMouseXPos() < x + dest.w) and
        (getMouseYPos() > y and getMouseYPos() < y + dest.h) ){
        _isover = true;

    }
    else{
        _isover = false;
    }

    if(getMouseLeft() && isOver()){
        _ispressed = true;
        Mix_PlayChannel(-1, isOverSound, 0);

    }
    else{
        _ispressed = false;
    }
}

const char *Button::GetEntityName() {
    return EntityName;
}

void Button::SetEntityName(const char* newName) {
    EntityName = newName;
}

