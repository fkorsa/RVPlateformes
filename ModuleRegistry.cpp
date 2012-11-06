#include "ModuleRegistry.h"

ModuleRegistry::ModuleRegistry()
{
}

void ModuleRegistry::registerWindow(Window *window)
{
    this->window = window;
}

Window *ModuleRegistry::getWindow()
{
    return window;
}

void ModuleRegistry::registerInputManager(InputManager *inputManager)
{
    this->inputManager = inputManager;
}

InputManager *ModuleRegistry::getInputManager()
{
    return inputManager;
}
