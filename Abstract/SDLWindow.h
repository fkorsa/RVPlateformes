#ifndef SDLWINDOW_H
#define SDLWINDOW_H

//#define VRJUGGLER

#ifndef VRJUGGLER

#include <SDL/SDL.h>
#include <osgUtil/SceneView>

#include "../Constants.h"
#include "Module.h"

class ModuleRegistry;

class SDLWindow : public Module
{
public:
    SDLWindow(ModuleRegistry *moduleRegistry);
    void draw();
    osg::ref_ptr<osgUtil::SceneView> sceneView;
};

#endif // VRJUGGLER
#endif // SDLWINDOW_H
