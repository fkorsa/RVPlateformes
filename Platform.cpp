#include "Platform.h"

Platform::Platform(ModuleRegistry *moduleRegistry, const osg::Vec3 &center,
                   const osg::Vec3 &lengths, osg::Texture2D *texture) :
    isMovingPlatform(false)
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
    moduleRegistry->getDynamicsWorld()->addRigidBody(body, COL_FLOOR, COL_BALL);
    moduleRegistry->getRootNode()->addChild(matrixTransform);

    body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    body->setActivationState( DISABLE_DEACTIVATION );

    startPoint = center;
}

Platform* Platform::setMass(float mass) {
    body->setMassProps(mass,btVector3(0.,0.,0.));
}

Platform* Platform::setTranslatingPlatformParameters(const osg::Vec3 &endPoint, float movingSpeed)
{
    this->endPoint = endPoint;
    this->movingSpeed = movingSpeed;
    movesTowardEnd = true;
    isMovingPlatform = true;
    return this;
}

void Platform::update(double elapsed)
{
    if(isMovingPlatform)
    {
        osg::Vec3 movingVector;
        btTransform world;
        osg::Vec3 platformPos, restVector;
        double localSpeed = movingSpeed * elapsed;
        shakeMotion->getWorldTransform(world);
        platformPos = osgbCollision::asOsgVec3(world.getOrigin());
        if(movesTowardEnd)
        {
            restVector = platformPos - (endPoint - startPoint);
            if(restVector.length() > localSpeed)
            {
                movingVector = endPoint - startPoint;
                movingVector.normalize();
                movingVector *= localSpeed;
                movePlatform(movingVector);
            }
            else
            {
                movesTowardEnd = false;
            }
        }
        else
        {
            restVector = platformPos;
            if(restVector.length() > localSpeed)
            {
                movingVector = startPoint - endPoint;
                movingVector.normalize();
                movingVector *= localSpeed;
                movePlatform(movingVector);
            }
            else
            {
                movesTowardEnd = true;
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
    btTransform netTrans = moveTrans * world;
    shakeMotion->setWorldTransform(netTrans);
}
