#ifndef BALL_H
#define BALL_H

#include <osg/ShapeDrawable>
#include <osg/Geode>

#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbCollision/Utils.h>
#include <osgbInteraction/SaveRestoreHandler.h>
#include <osgbInteraction/DragHandler.h>

#include <btBulletDynamicsCommon.h>

#include "Constants.h"

class Ball
{
public:
    Ball(osg::Group* _rootNode,btDynamicsWorld * _dynamicsWorld);

    void moveLeft();
    void moveRight();
    void jump();

    btRigidBody* getBody();

private:

    osg::Group* rootNode;
    btDynamicsWorld * dynamicsWorld;
    osg::ref_ptr<osg::MatrixTransform> root;
    btRigidBody* body;

};

#endif // BALL_H
