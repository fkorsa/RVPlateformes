#include "Controller.h"

Controller::Controller()
{    
    window = new Window(SDL_STRATEGY);
    inputManager = new InputManager(SDL_STRATEGY);
    while(true)
    {
        if(inputManager->handleInput() == RETURN_EXIT)
        {
            break;
        }

        window->draw();
    }
}
