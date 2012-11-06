#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Window/Window.h"
#include "InputManager/InputManager.h"
#include "Constants.h"

class Controller
{
public:
    Controller();
private:
    Window *window;
    InputManager *inputManager;
};

#endif // CONTROLLER_H
