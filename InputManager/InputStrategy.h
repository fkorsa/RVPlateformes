#ifndef INPUTMANAGERSTRATEGY_H
#define INPUTMANAGERSTRATEGY_H

#include "Constants.h"

class InputStrategy
{
public:
    virtual ReturnStatus handleInput() = 0;
};

#endif // INPUTMANAGERSTRATEGY_H
