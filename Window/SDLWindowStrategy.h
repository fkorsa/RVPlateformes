#ifndef SDLWINDOWSTRATEGY_H
#define SDLWINDOWSTRATEGY_H

#include <SDL/SDL.h>
#include <osgUtil/SceneView>

#include "Window/WindowStrategy.h"

class SDLWindowStrategy : public WindowStrategy
{
public:
    SDLWindowStrategy();
    void draw();
private:
    osg::ref_ptr<osgUtil::SceneView> sceneView;
};

#endif // SDLWINDOWSTRATEGY_H
