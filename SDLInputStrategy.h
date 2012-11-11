#ifndef SDLINPUTMANAGERSTRATEGY_H
#define SDLINPUTMANAGERSTRATEGY_H

#define SDL

#ifdef SDL

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

#endif // SDL
#endif // SDLINPUTMANAGERSTRATEGY_H
