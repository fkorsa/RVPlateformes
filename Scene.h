#ifndef SCENE_H
#define SCENE_H

#include <osgUtil/SceneView>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/LightSource>
#include <osg/BoundingSphere>

#include <btBulletDynamicsCommon.h>

#include "Abstract/Module.h"
#include "Abstract/InputManager.h"
#include "Text2d.h"
#include "Text3d.h"
#include "3DEntities/Platform.h"
#include "Skybox.h"
#include "3DEntities/Pyramid.h"
#include "3DEntities/Ball.h"

class Scene : public Module
{
public:
    Scene();
    void createScene();
    void run(double elapsed);
private:
    void createLights();
    void resetLevel();
    void createLevel(int level);
    void setBallPos(btVector3 ballNewPos);

    btDynamicsWorld* initBulletEngine(); // Initialise le moteur de physique

    btDynamicsWorld* dynamicsWorld;
    osg::MatrixTransform *rootNode;
    btRigidBody *ballBody;
    Ball* ball;
    Text2D* text2d;
    Text3D* text3d;
    Platform *platforms[100];
    Pyramid *pyramids[100];
    int numPlatforms, numPyramids, currentLevel;
    float time_elapsed_lost, time_elapsed_begin, time_elapsed_end, cameraAngle;
    btVector3 *lastCheckpoint;
    bool allowMovement, hasStartedEndText;
    const osg::Vec3f textOffset = osg::Vec3f(-10, 0, 0);
    const int MAX_LEVEL = 2;
};

#endif // SCENE_H
