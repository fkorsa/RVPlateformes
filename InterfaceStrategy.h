#ifndef INPUTSTRATEGY_H
#define INPUTSTRATEGY_H

#include "InputManager.h"
#include "Constants.h"

class InterfaceStrategy
{
public:
    InterfaceStrategy(InputStrategyType strategy, InputManager *inputManager, Window *window);
private:
    InputManager *inputManager;
    Window *window;
};

#endif // INPUTSTRATEGY_H
