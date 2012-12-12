#ifndef BALL_H
#define BALL_H

#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgDB/ReadFile>


#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <btBulletDynamicsCommon.h>

#include "../Constants.h"
#include "../Abstract/ModuleRegistry.h"
#include "../Abstract/Module.h"
#include "../Abstract/MyMotionState.h"

class Ball : public Module
{
public:
    Ball(osg::Vec3f center, float radius, ModuleRegistry *moduleRegistry);

    void moveLeft();
    void moveRight();
    void moveBehind(float force);
    void moveFront(float force);
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
