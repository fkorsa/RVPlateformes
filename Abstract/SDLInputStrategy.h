#ifndef SDLINPUTMANAGERSTRATEGY_H
#define SDLINPUTMANAGERSTRATEGY_H

//#define VRJUGGLER

#ifndef VRJUGGLER

#include <SDL/SDL.h>

#include <QDebug>

#include "InputManager.h"

class SDLInputStrategy : public Module
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

#endif // VRJUGGLER
#endif // SDLINPUTMANAGERSTRATEGY_H
