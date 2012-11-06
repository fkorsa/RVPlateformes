#include "Controller.h"

Controller::Controller()
{    
    ModuleRegistry moduleRegistry;

    window = new Window(SDL_STRATEGY);
    moduleRegistry.registerWindow(window);
    window->setModuleRegistry(&moduleRegistry);

    inputManager = new InputManager();
    moduleRegistry.registerInputManager(inputManager);
    inputManager->setModuleRegistry(&moduleRegistry);

    // Test pour savoir si on utilise la SDL ou VRJuggler pour les input
    /* if(SDL) {}
    else {}*/
    inputStrategy = new SDLInputStrategy();

    while(true)
    {
        if(inputStrategy->handleInput() == RETURN_EXIT)
        {
            break;
        }

        window->draw();
    }
}
