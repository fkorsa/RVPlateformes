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

    btDynamicsWorld* initBulletEngine(); // Initialise le moteur de physique

    btDynamicsWorld * dynamicsWorld;
    osg::Group *rootNode;
    btRigidBody *ballBody;
    Ball* ball;
    Text2D* text2d;
    Text3D* text3d;
    Platform *platforms[100];
    int numPlatforms;
};

#endif // SCENE_H
