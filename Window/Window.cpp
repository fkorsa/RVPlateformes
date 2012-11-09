#include "Window.h"

Window::Window(StrategyType strategyType, ModuleRegistry *moduleRegistry)
{
    switch(strategyType)
    {
    case SDL_STRATEGY:
        windowStrategy = new SDLWindowStrategy(moduleRegistry);
        break;
    case VRJUGGLER_STRATEGY:
        windowStrategy = new VRJugglerWindowStrategy();
        break;
    }
}

void Window::draw()
{
    windowStrategy->draw();
}
