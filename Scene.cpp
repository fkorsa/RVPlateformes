#include "Scene.h"

Scene::Scene()
{
    rootNode = new osg::Group;

    // Bullet Engine initialisation
    // TODO: cleaning bullet before closing app.
    dynamicsWorld = initBulletEngine();

}

// Bullet engine initialisation
btDynamicsWorld* Scene::initBulletEngine()
{

    btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher * dispatcher = new btCollisionDispatcher( collisionConfiguration );
    btConstraintSolver * solver = new btSequentialImpulseConstraintSolver;

    // Anything outside this area won't be taken into account by bullet
    btVector3 worldAabbMin( -10000, -10000, -10000 );
    btVector3 worldAabbMax( 10000, 10000, 10000 );
    btBroadphaseInterface * inter = new btAxisSweep3( worldAabbMin, worldAabbMax, 1000 );

    // You can now use: dynamicsWorld->addRigidBody( btRigidBody ); to add an object the simulation
    btDynamicsWorld * dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, inter, solver, collisionConfiguration );

    dynamicsWorld->setGravity( btVector3( 0, 0, 9.8 ) );

    return( dynamicsWorld );
}

// Create a simple box with and add it to the physics engine
osg::MatrixTransform* Scene::createBox( const osg::Vec3& center, const osg::Vec3& lengths, float mass )
{
    osg::Vec3 l( lengths );
    osg::Box* box = new osg::Box( center, l.x(), l.y(), l.z() );
    osg::ShapeDrawable* shape = new osg::ShapeDrawable( box );
    shape->setColor( osg::Vec4( 1., 1., 1., 1. ) );
    osg::Geode* geode = new osg::Geode();
    geode->addDrawable( shape );

    // We need a MatrixTransform to move the box around
    osg::MatrixTransform* root = new osg::MatrixTransform;
    root->addChild( geode );

    // We add the box to the simulation
    btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG( geode );
        osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
    cr->_sceneGraph = root;
    cr->_shapeType = BOX_SHAPE_PROXYTYPE;
    cr->_mass = mass;
    cr->_restitution = 1.f;
    btRigidBody* body = osgbDynamics::createRigidBody( cr.get(), cs );
    dynamicsWorld->addRigidBody( body );

    return( root );
}

void Scene::createScene()
{

    // How to add a model to the scene
    osg::Node *  model = osgDB::readNodeFile("data/starthing.obj");
    osg::PositionAttitudeTransform * modelPAT = new osg::PositionAttitudeTransform();
    modelPAT->setPosition(osg::Vec3d(0, 0, -200));
    modelPAT->addChild(model);
    rootNode->addChild(modelPAT);

    // Add light
    osg::Light* light = new osg::Light();
    light->setLightNum(0);
    // we set the light's position via a PositionAttitudeTransform object
    light->setPosition(osg::Vec4f(1000.0, 1000.0, -200, 1.0));
    light->setDiffuse(osg::Vec4f(1, 0.0, 0, 0.5));
    light->setSpecular(osg::Vec4f(1.0, 1.0, 1.0, 1.0));
    light->setAmbient(osg::Vec4f(0.0, 0.0, 0.0, 1.0));
    osg::LightSource* lightsource = new osg::LightSource();
    lightsource->setLight(light);
    rootNode->addChild(lightsource);

    light = new osg::Light();
    light->setLightNum(1);
    // we set the light's position via a PositionAttitudeTransform object
    light->setPosition(osg::Vec4f(-1000.0, -1000.0, -200, 1.0));
    light->setDiffuse(osg::Vec4f(0, 1.0, 0, 0.5));
    light->setSpecular(osg::Vec4f(1.0, 1.0, 1.0, 1.0));
    light->setAmbient(osg::Vec4f(0.0, 0.0, 0.0, 1.0));
    lightsource = new osg::LightSource();
    lightsource->setLight(light);
    rootNode->addChild(lightsource);

    osg::StateSet* stateset = rootNode->getOrCreateStateSet();
    lightsource->setStateSetModes(*stateset, osg::StateAttribute::ON);

    // Test box
    osg::Vec3 lengths( 20, 20, 6 );
    osg::Vec3 center( 0., 0., -25. );
    rootNode->addChild(createBox(center, lengths, 1.f));

    moduleRegistry->getCamera()->setViewMatrixAsLookAt(osg::Vec3(0, 0, 0),
                                                       osg::Vec3(0, 0, -1),
                                                       osg::Vec3(0, 1, 0));

    moduleRegistry->getSceneView()->setSceneData(rootNode);


}

void Scene::run() {
    //osg::notify( osg::ALWAYS ) << "coucou" << std::endl;
    dynamicsWorld->stepSimulation( 1/60, 4, 1/60/4. );

}
