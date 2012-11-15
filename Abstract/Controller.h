#ifndef CONTROLLER_H
#define CONTROLLER_H

//#define VRJUGGLER

#include "InputManager.h"
#include "../Scene.h"
#include "ModuleRegistry.h"
#include "../Constants.h"

#include <osg/Timer>

#ifdef VRJUGGLER
#include <cstdlib>
#include "../VRJuggler/OsgNav.h"
#include <vrj/Kernel/Kernel.h>
#else
#include "SDLWindow.h"
#include "SDLInputStrategy.h"
#endif // VRJUGGLER

class Controller
{
public:
    Controller(int argc, char * argv[]);

private:
#ifndef VRJUGGLER
    SDLWindow *window;
    SDLInputStrategy *inputStrategy;
#endif
    InputManager *inputManager;    
    Scene *scene;
    osg::Timer osgTimer;
    osg::Timer_t currentTime;
    osg::Timer_t previousTime;
};

#endif // CONTROLLER_H

