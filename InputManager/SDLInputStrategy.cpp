#include "SDLInputStrategy.h"

SDLInputStrategy::SDLInputStrategy()
{
    SDL_WM_GrabInput(SDL_GRAB_ON);
    SDL_ShowCursor(SDL_DISABLE);
}

ReturnStatus SDLInputStrategy::handleInput()
{
    SDL_Event event;
    bool alreadyPolledMouse = false;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                return RETURN_EXIT;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return RETURN_EXIT;
                }
                break;

            case SDL_MOUSEMOTION:
                // If there are several mouse event queued, we handle one and destroy the rest.
                if(!alreadyPolledMouse)
                {
                    handleMouseMotion(event);
                    alreadyPolledMouse = true;
                }
            break;

            default:
                break;
        }
    }

    handleKeyContinouslyPressed();

    return RETURN_NORMAL;
}

void SDLInputStrategy::handleKeyContinouslyPressed()
{
    Uint8 * keystate = SDL_GetKeyState(NULL);

    if(keystate[SDLK_a])
    {
        moduleRegistry->getInputManager()->walk(WALKING_PARALLEL, -SDL_WALKING_DISTANCE);
    }
    if(keystate[SDLK_s])
    {
        moduleRegistry->getInputManager()->walk(WALKING_FRONT, -SDL_WALKING_DISTANCE);
    }
    if(keystate[SDLK_d])
    {
        moduleRegistry->getInputManager()->walk(WALKING_PARALLEL, SDL_WALKING_DISTANCE);
    }
    if(keystate[SDLK_w])
    {
        moduleRegistry->getInputManager()->walk(WALKING_FRONT, SDL_WALKING_DISTANCE);
    }
}

void SDLInputStrategy::handleMouseMotion(SDL_Event event)
{
    if(event.motion.xrel != 0.0)
    {
        moduleRegistry->getInputManager()->rotateCamera(CAMERA_DIRECTION_X, ((float)event.motion.xrel)/100);
    }
    if(event.motion.yrel != 0.0)
    {
        moduleRegistry->getInputManager()->rotateCamera(CAMERA_DIRECTION_Y, ((float)event.motion.yrel)/100);
    }
}
