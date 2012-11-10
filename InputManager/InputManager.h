#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Module.h"
#include "Constants.h"
#include "Ball.h"

#include <osg/Math>
#include <QDebug>

class InputManager : public Module
{
public:
    InputManager();

    void walk(WalkingDirection dir, float distance);
    void rotateCamera(CameraDirection dir, float angle);

    // Déplace la balle
    void moveLeft();
    void moveRight();
    void jump();

    void setBall(Ball* _ball);

private:

    Ball* ball;


};

#endif // INPUTMANAGER_H
