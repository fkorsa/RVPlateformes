#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Constants.h"
#include "SDLInputStrategy.h"
#include "VRJugglerInputStrategy.h"

class InputStrategy;
class SDLInputStrategy;
class VRJugglerInputStrategy;

class InputManager
{
public:
    InputManager(StrategyType strategyType);
    ReturnStatus handleInput();
private:
    InputStrategy *inputStrategy;
};

#endif // INPUTMANAGER_H
