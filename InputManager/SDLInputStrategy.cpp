#include "SDLInputStrategy.h"

SDLInputStrategy::SDLInputStrategy() :
    qwerty(false),
    godmode(false),
    inputManager(NULL)
{
    SDL_WM_GrabInput(SDL_GRAB_ON);
    SDL_ShowCursor(SDL_DISABLE);
}

ReturnStatus SDLInputStrategy::handleInput()
{
    SDL_Event event;
    bool alreadyPolledMouse = false;
    if(!inputManager)
    {
        inputManager = moduleRegistry->getInputManager();
    }
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
                if(!alreadyPolledMouse && godmode)
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
                inputManager->moveLeft();
            }
        }
        else
        {
            if(keystate[SDLK_q])
            {
                inputManager->moveLeft();
            }   
        }
        if(keystate[SDLK_d])
        {
            inputManager->moveRight();
        }
        if(keystate[SDLK_SPACE])
        {
            inputManager->jump();
        }
    }
    else
    {
        // GODMODE
        if(qwerty)
        {
            if(keystate[SDLK_a])
            {
                inputManager->walk(WALKING_PARALLEL, -SDL_WALKING_DISTANCE);
            }

            if(keystate[SDLK_w])
            {
                inputManager->walk(WALKING_FRONT, SDL_WALKING_DISTANCE);
            }
        }
        else
        {
            if(keystate[SDLK_q])
            {
                inputManager->walk(WALKING_PARALLEL, -SDL_WALKING_DISTANCE);
            }
            if(keystate[SDLK_z])
            {
                inputManager->walk(WALKING_FRONT, SDL_WALKING_DISTANCE);
            }
        }
        if(keystate[SDLK_s])
        {
            inputManager->walk(WALKING_FRONT, -SDL_WALKING_DISTANCE);
        }
        if(keystate[SDLK_d])
        {
            inputManager->walk(WALKING_PARALLEL, SDL_WALKING_DISTANCE);
        }
    }
}

void SDLInputStrategy::handleMouseMotion(SDL_Event event)
{
    if(event.motion.xrel != 0.0)
    {
        inputManager->rotateCamera(CAMERA_DIRECTION_X, ((float)event.motion.xrel)/100);
    }
    if(event.motion.yrel != 0.0)
    {
        inputManager->rotateCamera(CAMERA_DIRECTION_Y, ((float)event.motion.yrel)/100);
    }
}
