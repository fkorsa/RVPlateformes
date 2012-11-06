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
                return handleKeyPressed(event);

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

    return RETURN_NORMAL;
}

ReturnStatus SDLInputStrategy::handleKeyPressed(SDL_Event event)
{
    switch(event.key.keysym.sym)
    {
        case SDLK_ESCAPE:
            return RETURN_EXIT;
        case SDLK_w:
            break;
        case SDLK_a:
            break;
        case SDLK_s:
            break;
        case SDLK_d:
            break;
        default:
            break;
    }
    return RETURN_NORMAL;
}

void SDLInputStrategy::handleMouseMotion(SDL_Event event)
{

}
