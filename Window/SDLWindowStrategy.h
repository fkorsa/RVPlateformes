#ifndef SDLWINDOWSTRATEGY_H
#define SDLWINDOWSTRATEGY_H

#include <SDL/SDL.h>
#include <osg/CameraNode>
#include <osgUtil/SceneView>

#include "Window/WindowStrategy.h"

class SDLWindowStrategy : public WindowStrategy
{
public:
    SDLWindowStrategy();
};

#endif // SDLWINDOWSTRATEGY_H
