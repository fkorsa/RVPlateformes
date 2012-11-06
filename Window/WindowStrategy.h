#ifndef WINDOWSTRATEGY_H
#define WINDOWSTRATEGY_H

#include <SDL/SDL.h>
#include <osg/CameraNode>
#include <osgUtil/SceneView>

class WindowStrategy
{
public:
    virtual WindowStrategy() = 0;
    virtual void draw() = 0;
};

#endif // WINDOWSTRATEGY_H
