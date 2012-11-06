#ifndef INPUTSTRATEGY_H
#define INPUTSTRATEGY_H

#include "InputManager.h"
#include "Constants.h"
#include "Window.h"

class InterfaceStrategy
{
public:
    InterfaceStrategy(InputStrategyType strategy);
private:
    InputManager *inputManager;
    Window *window;
};

#endif // INPUTSTRATEGY_H
