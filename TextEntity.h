
// Created by gabriel on 23/01/18.
//

#ifndef MARIOLIKEV1_TEXTENTITY_H
#define MARIOLIKEV1_TEXTENTITY_H

#include "guiEntity.h"
#include <SDL2/SDL.h>

class TextEntity : public guiEntity {

public:
    TextEntity(const char* text, int x1, int y1, int x2, int y2);

    virtual void Render(SDL_Renderer* rend);
    virtual void setTexture(SDL_Renderer* rend);
    virtual void setText(const char*, SDL_Renderer* _renderer);
    virtual const char* GetEntityName();
    virtual void SetEntityName(const char* newName);
    virtual void listenEvents();
    const char* EntityName;

private:
    const char* Message;
    SDL_Rect destR;
    SDL_Texture* texture;
};


#endif //MARIOLIKEV1_TEXTENTITY_H
