#ifndef INPUTMANAGERSTRATEGY_H
#define INPUTMANAGERSTRATEGY_H

#include "Constants.h"
#include "Module.h"
#include "InputManager/InputManager.h"

class InputStrategy : public Module
{
public:
    virtual ReturnStatus handleInput() = 0;
};

#endif // INPUTMANAGERSTRATEGY_H
