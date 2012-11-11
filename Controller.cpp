#include "Controller.h"

Controller::Controller()
{    
    ModuleRegistry moduleRegistry;
    int loopCnt = 0;

    window = new Window(SDL_STRATEGY, &moduleRegistry);
    moduleRegistry.registerWindow(window);
    window->setModuleRegistry(&moduleRegistry);

    inputManager = new InputManager();
    moduleRegistry.registerInputManager(inputManager);
    inputManager->setModuleRegistry(&moduleRegistry);

    scene = new Scene();
    moduleRegistry.registerScene(scene);
    scene->setModuleRegistry(&moduleRegistry);
    scene->createScene();

    // Test pour savoir si on utilise la SDL ou VRJuggler pour les inputs
    /* if(SDL) {}
    else {}*/
    inputStrategy = new SDLInputStrategy();
    inputStrategy->setModuleRegistry(&moduleRegistry);
    while(true)
    {
        if(inputStrategy->handleInput() == RETURN_EXIT)
        {
            break;
        }

        scene->run();

        window->draw();
        if(loopCnt<3)
        {
            loopCnt++;
            moduleRegistry.getCamera()->setViewMatrixAsLookAt(osg::Vec3(140, -400, 50),
                                                               osg::Vec3(140, 0, 50),
                                                               osg::Vec3(0, 0, 1));
        }
    }
}
