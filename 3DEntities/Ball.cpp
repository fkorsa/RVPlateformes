#include "Ball.h"

Ball::Ball(osg::Vec3f center, float radius, ModuleRegistry *moduleRegistry)
    :allowJump(false), jumping(false), timer()
{

    osg::Image* image = osgDB::readImageFile("data/textures/earth.jpg");
    osg::Texture2D* texture = new osg::Texture2D;
    osg::Sphere* sphere = new osg::Sphere(osg::Vec3f(), radius);
    osg::ShapeDrawable* shape = new osg::ShapeDrawable( sphere );
    osg::Geode* geode = new osg::Geode();
    osg::StateSet* state = new osg::StateSet();
    texture->setImage(image);
    state->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
    geode->addDrawable( shape );
    geode->setStateSet(state);

    osg::ref_ptr<osg::MatrixTransform> ballMT = new osg::MatrixTransform;
    ballMT->addChild(geode);
    osg::Matrix m;
    m.makeTranslate(center);
    ballMT->setMatrix( m );

    MyMotionState* ballMotionState = new MyMotionState(ballMT);

    btVector3 inertia(0, 0, 0);
    btCompoundShape* cs = new btCompoundShape;
    btSphereShape* sphereShape = new btSphereShape(7.);
    btTransform trans;
    trans.setIdentity();
    cs->addChildShape(trans, sphereShape);
    btRigidBody::btRigidBodyConstructionInfo rb(4.0f, ballMotionState, cs, inertia);

    body = new btRigidBody(rb);
    body->setActivationState(DISABLE_DEACTIVATION);

    ghost = new btPairCachingGhostObject();
    ghost->setCollisionShape (cs);
    ghost->setCollisionFlags (body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);

    moduleRegistry->getDynamicsWorld()->addRigidBody(body, COL_BALL, COL_FLOOR|COL_OTHERS);
    moduleRegistry->getDynamicsWorld()->addCollisionObject(ghost, COL_BALL, COL_FLOOR|COL_OTHERS);
    moduleRegistry->getRootNode()->addChild(ballMT.get());
}

void Ball::update(double elapsed)
{

    allowJump = false;

    // Superpose the ghost and the ball
    ghost->setWorldTransform(body->getWorldTransform());
    btBroadphasePairArray& pairArray = ghost->getOverlappingPairCache()->getOverlappingPairArray();
    // Il faut déterminer si la sphère touche le sol pour voir si droit de sauter
    collisionObject = NULL;
    for (int i=0;i<pairArray.size();i++)
    {
        const btBroadphasePair& pair = pairArray[i];
        if (pair.m_pProxy1->m_collisionFilterGroup == COL_FLOOR)
        {
            // Ball touche le sol
            allowJump = true;
            collisionObject = pair.m_pProxy1->m_clientObject;
            //osg::notify( osg::ALWAYS ) << "TOUCHE SOL" << std::endl;
            // Slow the ball down as it touches the ground
            body->applyCentralForce(body->getLinearVelocity()*-18.f);
            break;
        }
    }

    if (jumping)
    {
        //osg::notify( osg::ALWAYS ) << "JUMP " << std::endl;
        timer += elapsed;
        if (timer>1./10.) jumping = false;
        body->applyCentralForce(btVector3(0.,0.,BALL_JUMP_FORCE));
    }
    else
    {
        timer = 0;
    }
}

void Ball::moveLeft()
{
    if(allowJump)
        body->applyCentralForce(btVector3(0.,-BALL_HORIZONTAL_FORCE,0.));
}

void Ball::moveRight()
{
    if(allowJump)
        body->applyCentralForce(btVector3(0.,BALL_HORIZONTAL_FORCE,0.));
}

void Ball::moveBehind()
{
    if(allowJump)
        body->applyCentralForce(btVector3(-BALL_HORIZONTAL_FORCE,0.,0.));
}

void Ball::moveFront()
{
    if(allowJump)
        body->applyCentralForce(btVector3(BALL_HORIZONTAL_FORCE,0.,0.));
}

void Ball::jump()
{
    if(allowJump)
    {
        jumping= true;
    }
}

void *Ball::isOnTheFloor()
{
    return collisionObject;
}

btRigidBody *Ball::getBody()
{
    return body;
}
