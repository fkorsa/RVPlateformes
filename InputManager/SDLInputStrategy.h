#ifndef SDLINPUTMANAGERSTRATEGY_H
#define SDLINPUTMANAGERSTRATEGY_H

#include <SDL/SDL.h>

#include "InputStrategy.h"

class SDLInputStrategy : public InputStrategy
{
public:
    SDLInputStrategy();
    ReturnStatus handleInput();
    ReturnStatus handleKeyPressed(SDL_Event event);
    void handleMouseMotion(SDL_Event event);
};

#endif // SDLINPUTMANAGERSTRATEGY_H
