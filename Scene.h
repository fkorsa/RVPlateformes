#ifndef SCENE_H
#define SCENE_H

#include <osgUtil/SceneView>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/LightSource>

#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbCollision/Utils.h>
#include <osgbInteraction/SaveRestoreHandler.h>
#include <osgbInteraction/DragHandler.h>

#include <btBulletDynamicsCommon.h>

#include "Module.h"

class Scene : public Module
{
public:
    Scene();
    void createScene();
    void run();
private:
    void createLights();
    osg::MatrixTransform* createBox(const osg::Vec3& center, const osg::Vec3& lengths, float mass);
    btDynamicsWorld* initBulletEngine();
    btDynamicsWorld * dynamicsWorld;
    osg::Group *rootNode;
    osg::Timer osgTimer;
    osg::Timer_t currentTime;
    osg::Timer_t previousTime;
};

#endif // SCENE_H
