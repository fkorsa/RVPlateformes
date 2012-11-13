#include "Platform.h"

Platform::Platform(ModuleRegistry *moduleRegistry, const osg::Vec3 &center,
                   const osg::Vec3 &lengths, osg::Texture2D *texture) :
    isPlatformMoving(false),
    isUnstable(false)
{
    osg::Box* box = new osg::Box(osg::Vec3(), lengths.x(), lengths.y(), lengths.z());
    osg::ShapeDrawable* shape = new osg::ShapeDrawable(box);
    osg::StateSet* state = new osg::StateSet();
    osg::Geode* geode = new osg::Geode();
    shape->setColor(osg::Vec4(1., 1., 1., 1.));
    state->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
    geode->addDrawable(shape);
    geode->setStateSet(state);
    // We need a MatrixTransform to move the box around
    osg::MatrixTransform* matrixTransform = new osg::MatrixTransform;
    platformPAT = new osg::PositionAttitudeTransform;
    platformPAT->addChild(geode);
    platformPAT->setPosition(center);
    matrixTransform->addChild(platformPAT);

    shakeMotion = new osgbDynamics::MotionState();
    shakeMotion->setTransform(matrixTransform);

    btVector3 inertia(0, 0, 0);
    btCompoundShape* cs = new btCompoundShape;
    btBoxShape* boxShape = new btBoxShape(osgbCollision::asBtVector3(lengths*0.5));
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(osgbCollision::asBtVector3(center));
    cs->addChildShape(trans, boxShape);
    btRigidBody::btRigidBodyConstructionInfo rb(0.0f, shakeMotion, cs, inertia);

    body = new btRigidBody(rb);
    moduleRegistry->getDynamicsWorld()->addRigidBody(body, COL_FLOOR, COL_BALL);
    moduleRegistry->getRootNode()->addChild(matrixTransform);

    body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);

    startPoint = center;
}

Platform* Platform::setMass(float mass)
{
    body->setMassProps(mass,btVector3(0.,0.,0.));
}

// Make the platform move between its creating point (startPoint) and the parameter endPoint, at
// speed movingSpeed (which is in an arbitrary unit)
Platform* Platform::setTranslatingPlatformParameters(const osg::Vec3 &endPoint, float movingSpeed)
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

Platform* Platform::setUnstable()
{
    isUnstable = true;
    firstRotateDirection = true;
    rotatingAngle = 0;
    return this;
}

void Platform::update(double elapsed)
{
    // If the time elapsed is too great, do nothing
    if(elapsed < 1)
    {
//        btTransform world;
//        shakeMotion->getWorldTransform(world);
//        currentPos = osgbCollision::asOsgVec3(world.getOrigin()) + startPoint;
        // If the platform shall move between two points, as set by calling setTranslatingPlatformParameters(...)
        if(isPlatformMoving)
        {
            osg::Vec3 movingVector;
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
        if(isUnstable)
        {
            if(firstRotateDirection)
            {
                rotatePlatform(rotatingAngle);
                rotatingAngle += 0.01;
                if(rotatingAngle > 0.05)
                {
                    firstRotateDirection = false;
                }
            }
            else
            {
                rotatePlatform(rotatingAngle);
                rotatingAngle -= 0.01;
                if(rotatingAngle < -0.05)
                {
                    firstRotateDirection = true;
                }
            }
        }
    }
}

// Translates the platform by adding movingVector to its present coordinates
void Platform::movePlatform(osg::Vec3 movingVector)
{
    btVector3 move = osgbCollision::asBtVector3(movingVector);
    btTransform moveTrans;
    moveTrans.setIdentity();
    moveTrans.setOrigin(move);
    btTransform world;
    shakeMotion->getWorldTransform(world);
    world = moveTrans * world;
    shakeMotion->setWorldTransform(world);
}

void Platform::rotatePlatform(float angle)
{
    platformPAT->setAttitude(osg::Quat(1, 0, 0, angle));
    //platformPAT->setPosition(currentPos*2);
}
