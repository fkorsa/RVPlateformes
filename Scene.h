#ifndef SCENE_H
#define SCENE_H

#include <osgUtil/SceneView>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/LightSource>
#include <osg/BoundingSphere>

#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbCollision/RefBulletObject.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbDynamics/CreationRecord.h>
#include <osgbCollision/Utils.h>
#include <osgbInteraction/SaveRestoreHandler.h>
#include <osgbInteraction/DragHandler.h>

#include <btBulletDynamicsCommon.h>

#include "Abstract/Module.h"
#include "Abstract/InputManager.h"
#include "3DEntities/Ball.h"
#include "Text2d.h"
#include "Text3d.h"
#include "3DEntities/Platform.h"
#include "Skybox.h"
#include "3DEntities/Pyramid.h"

class Scene : public Module
{
public:
    Scene();
    void createScene();
    void run(double elapsed);
private:
    void createLights();


    // Ajoute la balle que le joueur doit déplacer
    osg::MatrixTransform* createBall( const osg::Vec3& center, float radius, float mass );
    // Ajoute une plate-forme
    osg::MatrixTransform* createBox(const osg::Vec3& center, const osg::Vec3& lengths, float mass, osg::Texture2D * texture);
    // Ajoute un modele
    osg::PositionAttitudeTransform *createModel(const char* filename, const osg::Vec3& center, const float scale,
                                                float mass, osg::ref_ptr<osgbInteraction::SaveRestoreHandler> srh);

    btDynamicsWorld* initBulletEngine(); // Initialise le moteur de physique

    btDynamicsWorld * dynamicsWorld;
    osg::MatrixTransform *rootNode;
    btRigidBody *ballBody;
    Ball* ball;
    Text2D* text2d;
    Text3D* text3d;
    Platform *platforms[100];
    int numPlatforms;
};

#endif // SCENE_H
