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

#include <QDebug>

#include "Module.h"
#include "InputManager/InputManager.h"
#include "Ball.h"

class Scene : public Module
{
public:
    Scene();
    void createScene();
    void run();
private:
    void createLights();


    // Ajoute la balle que le joueur doit déplacer
    osg::MatrixTransform* createBall( const osg::Vec3& center, float radius, float mass );
    // Ajoute une plate-forme
    osg::MatrixTransform* createBox(const osg::Vec3& center, const osg::Vec3& lengths, float mass);
    // Ajoute un modele
    osg::PositionAttitudeTransform *createModel(const char* filename, const osg::Vec3& center, const float scale,
                                                float mass, osg::ref_ptr<osgbInteraction::SaveRestoreHandler> srh);

    btDynamicsWorld* initBulletEngine(); // Initialise le moteur de physique

    btDynamicsWorld * dynamicsWorld;
    osg::Group *rootNode;
    osg::Timer osgTimer;
    osg::Timer_t currentTime;
    osg::Timer_t previousTime;
    btRigidBody *ballBody;
};

#endif // SCENE_H
