//
// Created by gabriel on 23/01/18.
//

#ifndef MARIOLIKEV1_CAMERA_H
#define MARIOLIKEV1_CAMERA_H


class Camera {
public:
    Camera(int Width,int Height);
    void ListenEvents(int* keyboardState);
    int x,y;
private:
    int _width, _height;
    float speed = 2.0f;
};


#endif //MARIOLIKEV1_CAMERA_H
