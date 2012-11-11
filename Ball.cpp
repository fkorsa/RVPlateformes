#include "Ball.h"

Ball::Ball(osg::Group* _rootNode, btDynamicsWorld * _dynamicsWorld)
{

    osg::Sphere* sphere = new osg::Sphere( osg::Vec3(0,0,20) , 7. );
    osg::ShapeDrawable* shape = new osg::ShapeDrawable( sphere );
    shape->setColor( osg::Vec4( 1., 0., 0., 1. ) );
    osg::Geode* geode = new osg::Geode();
    geode->addDrawable( shape );

    // We need a MatrixTransform to move the box around
    osg::MatrixTransform* root = new osg::MatrixTransform;
    root->addChild( geode );

    // We add the box to the simulation
    btCollisionShape* cs = osgbCollision::btSphereCollisionShapeFromOSG( geode );
    osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
    cr->_sceneGraph = root;
    cr->_shapeType = SPHERE_SHAPE_PROXYTYPE;
    cr->_mass = 3.f;
    cr->_restitution = 1.f;
    cr->_friction = 1.f;

    body = osgbDynamics::createRigidBody( cr.get(), cs );

    //body->setRollingFriction(1000.f);
    body->setFriction(100.f);

    _rootNode->addChild(root);
    _dynamicsWorld->addRigidBody(body);

}

void Ball::moveLeft()
{
    btVector3 velocity = body->getVelocityInLocalPoint(btVector3(0, 0, 0));
    body->setLinearVelocity(btVector3(-BALL_SPEED_CONTROL,velocity.y(),velocity.z()));
}

void Ball::moveRight()
{
    btVector3 velocity = body->getVelocityInLocalPoint(btVector3(0, 0, 0));
    body->setLinearVelocity(btVector3(BALL_SPEED_CONTROL,velocity.y(),velocity.z()));
}

void Ball::jump()
{
    //body->setLinearVelocity(btVector3(0,0,BALL_SPEED_JUMP));
    body->applyCentralImpulse(btVector3(0,0,BALL_SPEED_JUMP));
}

btRigidBody *Ball::getBody()
{
    return body;
}
