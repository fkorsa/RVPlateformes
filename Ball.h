#ifndef BALL_H
#define BALL_H

#include "Constants.h"
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbCollision/Utils.h>
#include <osgbInteraction/SaveRestoreHandler.h>
#include <osgbInteraction/DragHandler.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <btBulletDynamicsCommon.h>

#include "Constants.h"
#include "Module.h"

class Ball : public Module
{
public:
    Ball(osg::MatrixTransform* _rootNode,btDynamicsWorld * _dynamicsWorld);

    void moveLeft();
    void moveRight();
    void jump();

    void* isOnTheFloor();

    btRigidBody* getBody();

    void update(double elapsed);

private:

    double timer;
    bool allowJump, jumping;
    osg::MatrixTransform* rootNode;
    btDynamicsWorld * dynamicsWorld;
    osg::ref_ptr<osg::MatrixTransform> root;
    btRigidBody* body;
    btPairCachingGhostObject* ghost; // Object use to detect collisions

    void* collisionObject;

};

#endif // BALL_H
