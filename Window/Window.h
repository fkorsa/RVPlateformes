#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "Constants.h"
#include "Window/WindowStrategy.h"
#include "Window/SDLWindowStrategy.h"
#include "Window/VRJugglerWindowStrategy.h"
#include "Module.h"

class ModuleRegistry;

class Window : public Module
{
public:
    Window(StrategyType strategyType, ModuleRegistry *moduleRegistry);
    void draw();
private:
    WindowStrategy *windowStrategy;
};

#endif // SDLWINDOW_H
