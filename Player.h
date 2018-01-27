//
// Created by gabriel on 23/01/18.
//

#ifndef MARIOLIKEV1_PLAYER_H
#define MARIOLIKEV1_PLAYER_H

#include "gameObject.h"

class Player : public gameObject {
public:
    Player();
    void setPos(int x, int y) override ;
    int getXPos() override ;
    int getYPos() override ;
    void Render() override ;
    void setXpos(int x) override;
    void setYpos(int y) override ;
    void Render(SDL_Renderer* rend) override ;
    void loadTextures(SDL_Renderer* rend) override ;
    void loadTextures() override ;
    void listenEvents(int* keyboardState) override ;
    void listenEvents() override {};
    int _direction = 0;
    bool isGround = true;
    float jumpSpeed = 5.0f;
    float grav = 0;
    void update();
    int direction;
    SDL_Rect destinaton, source;
    SDL_Texture* mainTexture;
    std::pair<int, int> position;
    float speed = 4.0f;
    int xpos, ypos;

};


#endif //MARIOLIKEV1_PLAYER_H
