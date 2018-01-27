//
// Created by gabriel on 23/01/18.
//

#include "Player.h"
#include "GameState.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <cassert>

Player::Player() {
    position.first = 0;
    position.second = 0;

    source.x = source.y = 0;
    source.h = source.w = 65;

    destinaton.w = destinaton.h = 200;
    destinaton.x = 0; destinaton.y = 500;

    ypos = 100;
}

void Player::setPos(int x, int y) {
    position.first = x;
    position.second = y;
}

int Player::getXPos() {
    return position.first;
}

int Player::getYPos() {
    return position.second;
}

void Player::Render(SDL_Renderer* rend) {

   // update();

    if(source.x > 64 * 6)
        source.x = 0;

    destinaton.x = xpos;
    destinaton.y = ypos;

    SDL_RenderCopy(rend, mainTexture, &source, &destinaton);
    //std::cout<<"Rendegind player\n";
}

void Player::Render() {

    std::cout<<getTicks()<<'\n';




    if(getTicks() % 2 == 0)
        source.x = 65;
    else
        source.x = 0;

    SDL_RenderCopy(getRenderer(), mainTexture, &source, NULL );
}

void Player::loadTextures(SDL_Renderer *rend) {

    SDL_Surface* temporary = SDL_LoadBMP("PlayerSprites2.bmp");



    if(temporary != nullptr){
        SDL_SetColorKey(temporary, SDL_TRUE, SDL_MapRGB(temporary->format, 255, 255, 255));
        std::cout<<"player texture loaded\n";
        mainTexture = SDL_CreateTextureFromSurface(rend, temporary);

    } else{
      std::cout<<"texture file not found :(\n";

    }
}

void Player::loadTextures() {
    //
    SDL_Surface* temporary = SDL_LoadBMP("PlayerSprites.bmp");

    if(temporary != nullptr){

        mainTexture = SDL_CreateTextureFromSurface(getRenderer(), temporary);
        std::cout<<"player texture loaded\n";
    } else{
      std::cout<<"texture file not found :(\n";

    }
}

void Player::listenEvents(int *keyboardState) {
    if(keyboardState[SDLK_a]){
        direction = 1;
    }
    else if(keyboardState[SDLK_d]) {
        direction = -1;
    }    else {
        direction = 0;
    }
    if(keyboardState[SDLK_SPACE]){
        isGround = false;
    }

    update();
}

void Player::update() {

    if(_direction != direction)
        source.x = 0;

    _direction = direction;



    if(getTicks() % 10 == 0 ) {
        source.x += 65;
    }
    else {
        source.x += 0;
    }

    if(direction == 1) {
        xpos += -speed;
        source.y = 65 * 2;
    }

    else if(direction == -1){
        xpos += speed;
        source.y = 65;
    }

    else if(direction == 0){
        source.y = 0;
    }


    if(isGround == false){
        std::cout<<ypos<<'\n';
        grav += 0.1f;
        ypos -= jumpSpeed - grav;


    }
    if(ypos > 110){
        isGround = true;

        ypos = 100;
    }

}

void Player::setXpos(int x) {
    xpos = x;
}

void Player::setYpos(int y) {
    ypos = y;
}


