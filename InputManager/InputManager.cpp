#include "InputManager.h"

InputManager::InputManager(StrategyType strategyType)
{
    switch(strategyType)
    {
    case SDL_STRATEGY:
        inputStrategy = new SDLInputStrategy();
        break;
    case VRJUGGLER_STRATEGY:
        inputStrategy = new VRJugglerInputStrategy();
        break;
    }
}

ReturnStatus InputManager::handleInput()
{
    return inputStrategy->handleInput();
}
