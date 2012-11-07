#include "Controller.h"

Controller::Controller()
{    
    ModuleRegistry moduleRegistry;

    window = new Window(SDL_STRATEGY, &moduleRegistry);
    moduleRegistry.registerWindow(window);
    window->setModuleRegistry(&moduleRegistry);

    scene = new Scene();
    moduleRegistry.registerScene(scene);
    scene->setModuleRegistry(&moduleRegistry);
    scene->createScene();

    inputManager = new InputManager();
    moduleRegistry.registerInputManager(inputManager);
    inputManager->setModuleRegistry(&moduleRegistry);

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

        window->draw();
    }
}
