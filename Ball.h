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

class Ball
{
public:
    Ball(osg::Group* _rootNode,btDynamicsWorld * _dynamicsWorld);

    void moveLeft();
    void moveRight();
    void jump();

    void update(double elapsed);

private:

    double timer;
    bool allowJump, jumping;
    osg::Group* rootNode;
    btDynamicsWorld * dynamicsWorld;
    osg::ref_ptr<osg::MatrixTransform> root;
    btRigidBody* body;
    btPairCachingGhostObject* ghost; // Object use to detect collisions

};

#endif // BALL_H
