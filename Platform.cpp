#include "Platform.h"

Platform::Platform(ModuleRegistry *moduleRegistry, const osg::Vec3 &center,
                   const osg::Vec3 &lengths, osg::Texture2D *texture) :
    isPlatformMoving(false),positionElasticity(0),isUnstable(false)
{
    osg::Box* box = new osg::Box(center, lengths.x(), lengths.y(), lengths.z());
    osg::ShapeDrawable* shape = new osg::ShapeDrawable(box);
    osg::StateSet* state = new osg::StateSet();
    osg::Geode* geode = new osg::Geode();
    shape->setColor(osg::Vec4(1., 1., 1., 1.));
    state->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
    geode->addDrawable(shape);
    geode->setStateSet(state);
    // We need a MatrixTransform to move the box around
    osg::MatrixTransform* matrixTransform = new osg::MatrixTransform;
    matrixTransform->addChild(geode);

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
    registry = moduleRegistry;
    registry->getDynamicsWorld()->addRigidBody(body, COL_FLOOR, COL_BALL);
    registry->getRootNode()->addChild(matrixTransform);
    body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    startPoint = center;
    desiredCurrentPos = startPoint;
}

Platform* Platform::setMass(float mass)
{
    int flags = body->getCollisionFlags();
    registry->getDynamicsWorld()->removeCollisionObject(body);
    body->setCollisionFlags(flags & ~btCollisionObject::CF_KINEMATIC_OBJECT);
    body->forceActivationState(ACTIVE_TAG);
    body->setMassProps(mass,btVector3(0,0,0));
    registry->getDynamicsWorld()->addRigidBody(body, COL_FLOOR, COL_BALL);
    return this;
}

// La plaque oscille quand on saute dessus
Platform* Platform::setPositionElasticity(float elasticity) {
    setMass(15.0f);
    body->setGravity(btVector3(0,0,0));
    body->setDamping(0.8f,0.8f);
    positionElasticity = elasticity;
    return this;
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

        }
    }

    if (positionElasticity > 0) {
        btTransform world;
        shakeMotion->getWorldTransform(world);
        osg::Vec3 position = osgbCollision::asOsgVec3(world.getOrigin()) + startPoint;
        body->applyCentralForce(osgbCollision::asBtVector3(desiredCurrentPos-position)*positionElasticity);
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
    btTransform netTrans = moveTrans * world;
    shakeMotion->setWorldTransform(netTrans);
}

void Platform::rotatePlatform()
{
    btTransform rotateTrans;
    //rotateTrans.setRotation();
}
