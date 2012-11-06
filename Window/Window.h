#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "Constants.h"
#include "Window/WindowStrategy.h"
#include "Window/SDLWindowStrategy.h"
#include "Window/VRJugglerWindowStrategy.h"

class Window
{
public:
    Window(StrategyType strategyType);
    void draw();
private:
    WindowStrategy *windowStrategy;
};

#endif // SDLWINDOW_H
