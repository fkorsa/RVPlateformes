#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Constants.h"
#include "SDLInputStrategy.h"
#include "VRJugglerInputStrategy.h"
#include "Module.h"

class InputStrategy;
class SDLInputStrategy;
class VRJugglerInputStrategy;
class ModuleRegistry;

class InputManager : public Module
{
public:
    InputManager();
};

#endif // INPUTMANAGER_H
