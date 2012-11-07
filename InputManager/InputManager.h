#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Module.h"
#include "Constants.h"

class InputManager : public Module
{
public:
    InputManager();
    void walk(Direction dir, float distance);
};

#endif // INPUTMANAGER_H
