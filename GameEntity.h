//
// Created by gabriel on 24/01/18.
//

#ifndef MARIOLIKEV1_GAMEENTITY_H
#define MARIOLIKEV1_GAMEENTITY_H

#include <iostream>

class GameEntity {
public:
    GameEntity() = default;

    virtual ~GameEntity(){
        std::cout<<"deleting game entity\n";
    }
};


#endif //MARIOLIKEV1_GAMEENTITY_H
