#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Module.h"
#include "Constants.h"

#include <osg/Math>
#include <QDebug>

class InputManager : public Module
{
public:
    InputManager();
    void walk(WalkingDirection dir, float distance);
    void rotateCamera(CameraDirection dir, float angle);
};

#endif // INPUTMANAGER_H
