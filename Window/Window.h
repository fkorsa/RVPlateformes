#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL/SDL.h>
#include <osg/CameraNode>
#include <osgUtil/SceneView>

class Window
{
public:
    Window();
private:
    osg::ref_ptr<osgUtil::SceneView> sceneView;
    osg::ref_ptr<osg::CameraNode> playerCamera;
};

#endif // SDLWINDOW_H
