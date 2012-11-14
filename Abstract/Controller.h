#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDLWindow.h"
#include "InputManager.h"
#include "SDLInputStrategy.h"
#include "Scene.h"
#include "ModuleRegistry.h"
#include "Constants.h"

#ifdef VRJUGGLER
#include <cstdlib>
#include "VRJuggler/OsgNav.h"
#include <vrj/Kernel/Kernel.h>
#endif // VRJUGGLER

class Controller
{
public:
    Controller(int argc, char * argv[]);

private:
    SDLWindow *window;
    InputManager *inputManager;
    SDLInputStrategy *inputStrategy;
    Scene *scene;
    osg::Timer osgTimer;
    osg::Timer_t currentTime;
    osg::Timer_t previousTime;
};

#endif // CONTROLLER_H

