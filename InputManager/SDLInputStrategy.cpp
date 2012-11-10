#include "SDLInputStrategy.h"

SDLInputStrategy::SDLInputStrategy() :
    qwerty(false),godmode(false)
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
                else if(event.key.keysym.sym == SDLK_p)
                {
                    qwerty = !qwerty;
                }
                else if(event.key.keysym.sym == SDLK_m)
                {
                    godmode = !godmode;
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

    if (!godmode)
    {

        if(qwerty)
        {
            if(keystate[SDLK_a])
            {
                moduleRegistry->getInputManager()->moveLeft();
            }
            if(keystate[SDLK_d])
            {
                moduleRegistry->getInputManager()->moveRight();
            }
        }
        else
        {
            if(keystate[SDLK_q])
            {
                moduleRegistry->getInputManager()->moveLeft();
            }
            if(keystate[SDLK_d])
            {
                moduleRegistry->getInputManager()->moveRight();
            }
        }

    } else
    {

        // GODMODE

        if(qwerty)
        {
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
        else
        {
            if(keystate[SDLK_q])
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
            if(keystate[SDLK_z])
            {
                moduleRegistry->getInputManager()->walk(WALKING_FRONT, SDL_WALKING_DISTANCE);
            }
        }
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
