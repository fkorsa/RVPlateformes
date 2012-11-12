#include "Ball.h"

Ball::Ball(osg::MatrixTransform *_rootNode, btDynamicsWorld * _dynamicsWorld)
    :allowJump(false), jumping(false), timer()
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
    btCollisionShape* cs = new btSphereShape(6.9f);
    osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
    cr->_sceneGraph = root;
    cr->_shapeType = SPHERE_SHAPE_PROXYTYPE;
    cr->_mass = 3.f;
    cr->_restitution = 0.0f;
    cr->_friction = 1.f;

    body = osgbDynamics::createRigidBody( cr.get(), cs );

    body->setActivationState( DISABLE_DEACTIVATION );

    ghost = new btPairCachingGhostObject();
    ghost->setCollisionShape (cs);
    ghost->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

    _rootNode->addChild(root);
    _dynamicsWorld->addRigidBody(body,COL_BALL,COL_FLOOR);
    _dynamicsWorld->addCollisionObject(ghost,COL_BALL,COL_FLOOR);
}

void Ball::update(double elapsed)
{

    allowJump = false;

    // Superpose the ghost and the ball
    ghost->setWorldTransform(body->getWorldTransform());
    btBroadphasePairArray& pairArray = ghost->getOverlappingPairCache()->getOverlappingPairArray();
    // Il faut déterminer si la sphère touche le sol pour voir si droit de sauter
    for (int i=0;i<pairArray.size();i++)
    {
        const btBroadphasePair& pair = pairArray[i];
        if (pair.m_pProxy1->m_collisionFilterGroup == COL_FLOOR)
        {
            // Ball touche le sol
            allowJump = true;
            //osg::notify( osg::ALWAYS ) << "TOUCHE SOL" << std::endl;
            // Slow the ball down as it touches the ground
            body->applyCentralForce(body->getLinearVelocity()*-13.f);
            break;
        }
    }

    if (jumping)
    {
        osg::notify( osg::ALWAYS ) << "JUMP " << std::endl;
        timer += elapsed;
        if (timer>1./10.) jumping = false;
        body->applyCentralForce(btVector3(0.,0.,3000.));
    }
    else
    {
        timer = 0;
    }

}

void Ball::moveLeft()
{
    if(allowJump)
        body->applyCentralForce(btVector3(-850.,0.,0.));
}

void Ball::moveRight()
{
    if(allowJump)
        body->applyCentralForce(btVector3(850.,0.,0.));
}

void Ball::jump()
{
    if(allowJump)
    {
        jumping= true;
    }
}

btRigidBody *Ball::getBody()
{
    return body;
}
