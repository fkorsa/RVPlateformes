#include "Platform.h"

Platform::Platform(ModuleRegistry *moduleRegistry, const osg::Vec3 &center,
                   const osg::Vec3 &lengths, osg::Texture2D *texture) :
    isPlatformMoving(false),positionElasticity(0)
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
    btRigidBody::btRigidBodyConstructionInfo rb(10.0f, shakeMotion, cs, inertia);

    body = new btRigidBody(rb);
    moduleRegistry->getDynamicsWorld()->addRigidBody(body, COL_FLOOR, COL_BALL);
    moduleRegistry->getRootNode()->addChild(matrixTransform);

    body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    body->setActivationState( DISABLE_DEACTIVATION );

    startPoint = center;
}

Platform* Platform::setMass(float mass)
{
    body->setCollisionFlags(body->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT & ~btCollisionObject::CF_STATIC_OBJECT);
    body->forceActivationState(ACTIVE_TAG);
    return this;
}

// La plaque oscille quand on saute dessus
Platform* Platform::setPositionElasticity(float elasticity) {
    setMass(5.0f);
    positionElasticity = elasticity;
    return this;
}

Platform* Platform::setTranslatingPlatformParameters(const osg::Vec3 &endPoint, float movingSpeed)
{
    this->endPoint = endPoint;
    this->movingSpeed = movingSpeed;
    movesTowardEnd = true;
    isPlatformMoving = true;
    currentPos = startPoint;
    return this;
}

void Platform::update(double elapsed)
{
    if(isPlatformMoving)
    {
        osg::Vec3 movingVector;
        double localSpeed = movingSpeed * elapsed;
        if(elapsed < 1)
        {
            if(movesTowardEnd)
            {
                if((currentPos-endPoint).length() > localSpeed)
                {
                    movingVector = endPoint - startPoint;
                    movingVector.normalize();
                    movingVector *= localSpeed;
                    movePlatform(movingVector);
                    currentPos += movingVector;
                }
                else
                {
                    movesTowardEnd = false;
                    currentPos = endPoint;
                }
            }
            else
            {
                if((currentPos-startPoint).length() > localSpeed)
                {
                    movingVector = startPoint - endPoint;
                    movingVector.normalize();
                    movingVector *= localSpeed;
                    movePlatform(movingVector);
                    currentPos += movingVector;
                }
                else
                {
                    movesTowardEnd = true;
                    currentPos = startPoint;
                }
            }
        }
    }

    if (positionElasticity > 0) {
        body->applyCentralForce((startPoint-currentPos)*positionElasticity);
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
