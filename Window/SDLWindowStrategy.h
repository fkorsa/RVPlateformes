#ifndef SDLWINDOWSTRATEGY_H
#define SDLWINDOWSTRATEGY_H

#include <SDL/SDL.h>
#include <osgUtil/SceneView>

#include "Window/WindowStrategy.h"
#include "ModuleRegistry.h"

class SDLWindowStrategy : public WindowStrategy
{
public:
    SDLWindowStrategy(ModuleRegistry *moduleRegistry);
    void draw();
private:
    osgUtil::SceneView *sceneView;
};

#endif // SDLWINDOWSTRATEGY_H
