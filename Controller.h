#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Window/Window.h"
#include "InputManager/InputManager.h"
#include "InputManager/InputStrategy.h"
#include "InputManager/SDLInputStrategy.h"
#include "InputManager/VRJugglerInputStrategy.h"
#include "ModuleRegistry.h"
#include "Constants.h"

class Controller
{
public:
    Controller();
private:
    Window *window;
    InputManager *inputManager;
    InputStrategy *inputStrategy;
};

#endif // CONTROLLER_H

