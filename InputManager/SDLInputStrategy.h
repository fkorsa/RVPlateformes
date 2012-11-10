#ifndef SDLINPUTMANAGERSTRATEGY_H
#define SDLINPUTMANAGERSTRATEGY_H

#include <SDL/SDL.h>

#include <QDebug>

#include "InputStrategy.h"

class SDLInputStrategy : public InputStrategy
{
public:
    SDLInputStrategy();
    ReturnStatus handleInput();
    void handleKeyContinouslyPressed();
    void handleMouseMotion(SDL_Event event);
private:
    bool qwerty;
    bool godmode;
    InputManager *inputManager;
};

#endif // SDLINPUTMANAGERSTRATEGY_H
