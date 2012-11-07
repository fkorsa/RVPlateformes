#ifndef SCENE_H
#define SCENE_H

#include <osgUtil/SceneView>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>

#include "Module.h"

class Scene : public Module
{
public:
    Scene();
    void createScene();
private:
    osg::Group *rootNode;
};

#endif // SCENE_H
