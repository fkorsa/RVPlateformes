#include "Platform.h"

Platform::Platform(ModuleRegistry *moduleRegistry, const osg::Vec3f &center,
                   const osg::Vec3f &lengths, osg::Texture2D *texture) :
    isPlatformMoving(false),positionElasticity(0),isUnstable(false)
{
    osg::Box* box = new osg::Box(osg::Vec3(), lengths.x(), lengths.y(), lengths.z());
    osg::ShapeDrawable* shape = new osg::ShapeDrawable(box);
    osg::StateSet* state = new osg::StateSet();
    osg::Geode* geode = new osg::Geode();
    shape->setColor(osg::Vec4(1., 1., 1., 1.));
    state->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
    geode->addDrawable(shape);
    geode->setStateSet(state);
    platformPAT = new osg::PositionAttitudeTransform;
    platformPAT->addChild(geode);
    platformPAT->setPosition(center);

    platformMotionState = new MyMotionState(platformPAT);

    btVector3 inertia(0, 0, 0);
    btCompoundShape* cs = new btCompoundShape;
    btBoxShape* boxShape = new btBoxShape(Utils::asBtVector3(lengths*0.5));
    btTransform trans;
    trans.setIdentity();
    cs->addChildShape(trans, boxShape);
    btRigidBody::btRigidBodyConstructionInfo rb(0.0f, platformMotionState, cs, inertia);

    body = new btRigidBody(rb);
    body->setFriction(1);
    body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    registry = moduleRegistry;
    registry->getDynamicsWorld()->addRigidBody(body, COL_FLOOR, COL_BALL|COL_OTHERS);
    registry->getRootNode()->addChild(platformPAT);
    startPoint = Utils::asBtVector3(center);
    desiredCurrentPos = startPoint;
}

Platform* Platform::setMass(float mass)
{
    int flags = body->getCollisionFlags();
    registry->getDynamicsWorld()->removeCollisionObject(body);
    body->setCollisionFlags(flags & ~btCollisionObject::CF_KINEMATIC_OBJECT);
    body->forceActivationState(ACTIVE_TAG);
    body->setMassProps(mass,btVector3(0,0,0));
    registry->getDynamicsWorld()->addRigidBody(body, COL_FLOOR, COL_BALL|COL_OTHERS);
    return this;
}

// La plaque oscille quand on saute dessus
// Plus elasticity est grand plus les oscillations sont lentes
// Plus resistance est grand plus le retour à l'équilibre est rapide
Platform* Platform::setPositionElasticity(float elasticity, float resistance)
{
    setMass(10.0f);
    body->setGravity(btVector3(0,0,0));
    body->setDamping(0.2f,0.2f);
    positionElasticity = elasticity;
    positionResistance = resistance;
    return this;
}

// Make the platform move between its creating point (startPoint) and the parameter endPoint, at
// speed movingSpeed (which is in an arbitrary unit)
Platform* Platform::setTranslatingPlatformParameters(const btVector3 &endPoint, float movingSpeed)
{
    this->endPoint = endPoint;
    this->movingSpeed = movingSpeed;
    // Initialize the movement direction to be toward the endPoint
    movesTowardEnd = true;
    // Set the platform type to be a moving platform
    isPlatformMoving = true;
    // Initialize the position of the platform
    desiredCurrentPos = startPoint;
    body->setActivationState(DISABLE_DEACTIVATION);
    return this;
}

Platform* Platform::setUnstable(float platformUnstability)
{
    isUnstable = true;
    firstRotateDirection = true;
    directionDelta = 0;
    rotatingDirection = 0;
    directionFactor = PLATFORM_UNSTABLE_SMOOTHING_THRESHOLD;
    this->platformUnstability = platformUnstability;
    return this;
}

void Platform::update(double elapsed)
{
    // If the time elapsed is too great, do nothing
    if(elapsed < 1)
    {
        // If the platform shall move between two points, as set by calling setTranslatingPlatformParameters(...)
        if(isPlatformMoving)
        {
            btVector3 movingVector;
            // We scale the speed by the time elapsed since the last passage in the loop
            double localSpeed = movingSpeed * elapsed;
            // Test the direction the platform should move
            if(movesTowardEnd)
            {
                // If the platform is not yet too close to the endPoint, move
                if((desiredCurrentPos-endPoint).length() > localSpeed)
                {
                    // The platform moves by a vector defined by the start point and the end point,
                    // normalized and scaled by the speed & time elapsed
                    movingVector = endPoint - startPoint;
                    movingVector.normalize();
                    movingVector *= localSpeed;
                    movePlatform(movingVector);
                    desiredCurrentPos += movingVector;
                }
                else
                {
                    movesTowardEnd = false;
                    desiredCurrentPos = endPoint;
                }
            }
            else
            {
                if((desiredCurrentPos-startPoint).length() > localSpeed)
                {
                    movingVector = startPoint - endPoint;
                    movingVector.normalize();
                    movingVector *= localSpeed;
                    movePlatform(movingVector);
                    desiredCurrentPos += movingVector;
                }
                else
                {
                    movesTowardEnd = true;
                    desiredCurrentPos = startPoint;
                }
            }
        }
        // If the platform shall fall after a certain time during which the ball is on the platform,
        // as set in setUnstable(...)
        if(isUnstable)
        {
            // Test whether the ball is in contact with this platform
            if(registry->getBall()->isOnTheFloor() == body)
            {
                directionDelta += platformUnstability * elapsed;
                rotatingDirection += directionDelta;
                if(directionFactor>1)
                {
                    directionFactor /= PLATFORM_UNSTABLE_SMOOTHING * elapsed;
                }
            }
            // else slowly stop the agitation
            else
            {
                if(directionFactor<PLATFORM_UNSTABLE_SMOOTHING_THRESHOLD)
                {
                    directionFactor *= PLATFORM_UNSTABLE_SMOOTHING * elapsed;
                }
            }
            // If the platform has been agitated for too long, it will fall
            if(rotatingDirection>PLATFORM_UNSTABLE_FALLING_THRESHOLD)
            {
                setMass(1.f);
                body->setGravity(btVector3(0, 0, -1000));
                positionElasticity = 0;
            }
            rotatePlatform(rotatingDirection, directionFactor);
        }
    }

    if (positionElasticity > 0)
    {
        btTransform world;
        platformMotionState->getWorldTransform(world);
        btVector3 position = world.getOrigin();
        body->applyCentralForce((desiredCurrentPos-position)*positionElasticity);
        body->applyCentralForce(-body->getLinearVelocity()*positionResistance);
    }

}

// Translates the platform by adding movingVector to its present coordinates
void Platform::movePlatform(btVector3 movingVector)
{
    btTransform moveTrans;
    moveTrans.setIdentity();
    moveTrans.setOrigin(movingVector);
    btTransform world;
    platformMotionState->getWorldTransform(world);
    world = moveTrans * world;
    platformMotionState->setWorldTransform(world);
}

// Rotate the platform to make the impression of agitation (like it will fall soon...)
void Platform::rotatePlatform(float direction, float directionFactor)
{
    platformPAT->setAttitude(osg::Quat(cos(direction)/directionFactor, sin(direction)/directionFactor,
                                       PLATFORM_UNSTABLE_ANGLE, 0));
}
