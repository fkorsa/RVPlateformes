#ifndef SDLINPUTMANAGERSTRATEGY_H
#define SDLINPUTMANAGERSTRATEGY_H

#include "InputStrategy.h"

class SDLInputStrategy : public InputStrategy
{
public:
    SDLInputStrategy();
    void handleInput();
};

#endif // SDLINPUTMANAGERSTRATEGY_H
