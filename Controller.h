#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Window/Window.h"
#include "InputManager/InputManager.h"
#include "InputManager/InputStrategy.h"
#include "InputManager/SDLInputStrategy.h"
#include "InputManager/VRJugglerInputStrategy.h"
#include "Scene.h"
#include "ModuleRegistry.h"
#include "Constants.h"

class Controller
{
public:
    Controller(StrategyType strategyType);
private:
    Window *window;
    InputManager *inputManager;
    InputStrategy *inputStrategy;
    Scene *scene;
};

#endif // CONTROLLER_H

