#ifndef VRJUGGLERINPUTMANAGERSTRATEGY_H
#define VRJUGGLERINPUTMANAGERSTRATEGY_H

#include "InputStrategy.h"

class VRJugglerInputStrategy : public InputStrategy
{
public:
    VRJugglerInputStrategy();
    ReturnStatus handleInput();
};

#endif // VRJUGGLERINPUTMANAGERSTRATEGY_H
