#include "Window.h"

Window::Window(StrategyType strategyType)
{
    switch(strategyType)
    {
    case SDL_STRATEGY:
        windowStrategy = new SDLWindowStrategy();
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
