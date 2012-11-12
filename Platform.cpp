#include "Platform.h"

Platform::Platform(ModuleRegistry *moduleRegistry, const osg::Vec3 &center,
                   const osg::Vec3 &lengths, float mass, osg::Texture2D *texture) :
    platformType(PLATFORM_STATIC)
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
    osg::Matrix matrixOffset;
    matrixOffset.setTrans(center);

    shakeMotion = new osgbDynamics::MotionState();
    shakeMotion->setTransform(matrixTransform);
    //matrixTransform->setMatrix(matrixOffset);

    // We add the box to the simulation
    btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG(geode);
    osg::ref_ptr<osgbDynamics::CreationRecord> cr = new osgbDynamics::CreationRecord;
    cr->_sceneGraph = matrixTransform;
    cr->_shapeType = BOX_SHAPE_PROXYTYPE;
    cr->_mass = mass;
    cr->_restitution = 1.f;
    cr->_friction = 1.f;
    btVector3 inertia(0, 0, 0);
    btRigidBody::btRigidBodyConstructionInfo rb( mass, shakeMotion, cs, inertia);
    //body = osgbDynamics::createRigidBody(cr.get(), cs);
    body = new btRigidBody(rb);
    //body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    moduleRegistry->getDynamicsWorld()->addRigidBody(body, COL_FLOOR, COL_BALL);
    moduleRegistry->getRootNode()->addChild(matrixTransform);

    btVector3 move(center.x(), center.y(), center.z());
    btTransform moveTrans;
    moveTrans.setIdentity();
    moveTrans.setOrigin(move);
    btTransform world;
    shakeMotion->getWorldTransform(world);
    btTransform netTrans = moveTrans * world;
    //shakeMotion->setWorldTransform(netTrans);
}

void Platform::setTranslatingPlatformParameters(const osg::Vec3 &originPoint, const osg::Vec3 &endPoint, float movingSpeed)
{
    this->originPoint = originPoint;
    this->endPoint = endPoint;
    this->movingSpeed = movingSpeed;
    platformType = PLATFORM_TRANSLATING;
    body->setActivationState( DISABLE_DEACTIVATION );
}

PlatformType Platform::getPlatformType()
{
    return platformType;
}

void Platform::update()
{
    switch(platformType)
    {
        case PLATFORM_TRANSLATING:
            //osg::Vec3d platformPosition = matrixTransform->getMatrix().getTrans();

            /*osg::notify( osg::ALWAYS ) << "Position : x " << platformPosition.x() <<
                                          " y " << platformPosition.y() <<
                                          " z " << platformPosition.z() << std::endl;*/
            /*body->forceActivationState(1);
            body->setLinearVelocity(btVector3(100, 100, 100));*/
            break;
    }
}
