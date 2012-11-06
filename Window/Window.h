#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "Constants.h"
#include "Window/WindowStrategy.h"
#include "Window/SDLWindowStrategy.h"
#include "Window/VRJugglerWindowStrategy.h"

class Window
{
public:
    Window(StrategyType strategyType);
private:
    WindowStrategy *windowStrategy;
    osg::ref_ptr<osgUtil::SceneView> sceneView;
    osg::ref_ptr<osg::CameraNode> playerCamera;
};

#endif // SDLWINDOW_H
