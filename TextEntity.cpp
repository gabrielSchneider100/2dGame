//
// Created by gabriel on 23/01/18.
//

#include "TextEntity.h"
#include <SDL2/SDL_ttf.h>

const char *TextEntity::GetEntityName() {
    return EntityName;
}

void TextEntity::SetEntityName(const char *newName) {
    EntityName = newName;
}

TextEntity::TextEntity(const char *text, int x1, int y1,
                       int x2, int y2): Message(text){
    destR.x = x1;
    destR.y = y1;
    destR.w = x2 - x1;
    destR.h = y2 - y1;

    SetEntityName(Message);

}

void TextEntity::setText(const char * text, SDL_Renderer *_renderer) {
    Message = text;
    setTexture(_renderer);
}

void TextEntity::Render(SDL_Renderer *rend) {
    SDL_RenderCopy(rend, texture, &destR, &destR);

}

void TextEntity::setTexture(SDL_Renderer *rend) {

    TTF_Font *Sans = TTF_OpenFont("Raleway.ttf", 50);

    if (Sans != NULL) {
        SDL_Color White = {255, 255, 255};
        SDL_Surface *messase = TTF_RenderText_Solid(Sans, Message, White);
        texture = SDL_CreateTextureFromSurface(rend, messase);

    std::cout << "text created!\n";
    } else {
    std::cout << "error text texture: " << TTF_GetError() << '\n';

    }
}

void TextEntity::listenEvents() {
   // std::cout<<"text listening to events\n";
}

