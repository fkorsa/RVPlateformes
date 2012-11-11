#include "Scene.h"

Scene::Scene()
{

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

    dynamicsWorld->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    dynamicsWorld->setGravity( btVector3( 0, 0, -190 ) );

    return( dynamicsWorld );
}

// Create a simple box with and add it to the physics engine
osg::MatrixTransform* Scene::createBox(const osg::Vec3& center, const osg::Vec3& lengths, float mass,
                                       osg::Texture2D* texture)
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
    osg::MatrixTransform* root = new osg::MatrixTransform;
    root->addChild(geode);

    // We add the box to the simulation
    btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG(geode);
    osg::ref_ptr<osgbDynamics::CreationRecord> cr = new osgbDynamics::CreationRecord;
    cr->_sceneGraph = root;
    cr->_shapeType = BOX_SHAPE_PROXYTYPE;
    cr->_mass = mass;
    cr->_restitution = 1.f;
    cr->_friction = 1.f;
    btRigidBody* body = osgbDynamics::createRigidBody(cr.get(), cs);
    dynamicsWorld->addRigidBody(body,COL_FLOOR,COL_BALL);

    return root;
}

osg::PositionAttitudeTransform* Scene::createModel(const char *filename, const osg::Vec3 &center,
                                                   const float scale, float mass,
                                                   osg::ref_ptr<osgbInteraction::SaveRestoreHandler> srh)
{
    osg::Node* modelNode = osgDB::readNodeFile(filename);
    if(modelNode == NULL)
    {
        qDebug() << "Can't load model.";
        return(NULL);
    }

    // We need a MatrixTransform to move the box around
    osg::MatrixTransform* matrixTransform = new osg::MatrixTransform;
    matrixTransform->addChild(modelNode);

    osg::PositionAttitudeTransform* root = new osg::PositionAttitudeTransform();
    root->addChild(matrixTransform);
    root->setScale(osg::Vec3(scale, scale, scale));
    root->setPosition(center);

    //btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG(modelNode);
    osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
    cr->_sceneGraph = matrixTransform;
    cr->_shapeType = BOX_SHAPE_PROXYTYPE;
    cr->_mass = mass;
    cr->_restitution = 1.f;
    btRigidBody* body = osgbDynamics::createRigidBody(cr.get());
    matrixTransform->setUserData(new osgbCollision::RefRigidBody(body));
    dynamicsWorld->addRigidBody(body);
    srh->add("", body);
    return root;
}

void Scene::createScene()
{
    rootNode = moduleRegistry->getRootNode();

    // How to add a model to the scene
    /*osg::Node *  model = osgDB::readNodeFile("data/starthing.obj");
    osg::PositionAttitudeTransform * modelPAT = new osg::PositionAttitudeTransform();
    modelPAT->setPosition(osg::Vec3d(0, 0, -200));
    modelPAT->addChild(model);
    rootNode->addChild(modelPAT);*/

    createLights();

    osg::ref_ptr<osgbInteraction::SaveRestoreHandler> srh = new osgbInteraction::SaveRestoreHandler;

    srh->capture();

    // 2D TEXT FOR DEBUGGING PURPOSE !
    text2d = new Text2D(rootNode);

    // THE MIGHTY BALL
    ball = new Ball(rootNode,dynamicsWorld);
    moduleRegistry->getInputManager()->setBall(ball);
    ballBody = ball->getBody();

    // NIVEAU 1
    osg::Image* image1 = osgDB::readImageFile("data/bric.jpg");
    osg::Texture2D* texture1 = new osg::Texture2D;
    texture1->setImage(image1);

    rootNode->addChild(createBox(osg::Vec3( 0., 0., -25. ), osg::Vec3(30, 30, 5), 0.f,texture1));
    rootNode->addChild(createBox(osg::Vec3( 60., 0., -15. ), osg::Vec3(30, 30, 5), 0.f,texture1));
    rootNode->addChild(createBox(osg::Vec3( 120., 0., -5. ), osg::Vec3(30, 30, 5), 0.f,texture1));
    rootNode->addChild(createBox(osg::Vec3( 180., 0., 5. ), osg::Vec3(30, 30, 5), 0.f,texture1));
    rootNode->addChild(createBox(osg::Vec3( 260., 0., 5. ), osg::Vec3(50, 50, 5), 0.f,texture1));

#ifndef VRJUGGLER
    moduleRegistry->getSceneView()->setSceneData(rootNode);
#endif
}

void Scene::createLights()
{
    // Add light
    osg::Light* light = new osg::Light();
    light->setLightNum(0);
    light->setPosition(osg::Vec4f(50.0, 0.0, 100, 1.0));
    light->setDiffuse(osg::Vec4f(1.0, 1.0, 1.0, 0.5));
    light->setSpecular(osg::Vec4f(1.0, 1.0, 1.0, 1.0));
    light->setAmbient(osg::Vec4f(0.0, 0.0, 0.0, 1.0));
    osg::LightSource* lightsource = new osg::LightSource();
    lightsource->setLight(light);
    rootNode->addChild(lightsource);

    /*light = new osg::Light();
    light->setLightNum(0);
    light->setPosition(osg::Vec4f(50.0, -100.0, 0.0, 1.0));
    light->setDiffuse(osg::Vec4f(1.0, 1.0, 1.0, 0.5));
    light->setSpecular(osg::Vec4f(1.0, 1.0, 1.0, 1.0));
    light->setAmbient(osg::Vec4f(0.0, 0.0, 0.0, 1.0));
    lightsource = new osg::LightSource();
    lightsource->setLight(light);
    rootNode->addChild(lightsource);*/

    /*light = new osg::Light();
    light->setLightNum(2);
    light->setPosition(osg::Vec4f(-1000.0, -1000.0, 200, 1.0));
    light->setDiffuse(osg::Vec4f(0, 0, 1, 0.5));
    light->setSpecular(osg::Vec4f(1.0, 1.0, 1.0, 1.0));
    light->setAmbient(osg::Vec4f(0.0, 0.0, 0.0, 1.0));
    lightsource = new osg::LightSource();
    lightsource->setLight(light);
    rootNode->addChild(lightsource);

    light = new osg::Light();
    light->setLightNum(3);
    light->setPosition(osg::Vec4f(1000.0, 1000.0, 200, 1.0));
    light->setDiffuse(osg::Vec4f(0, 1, 1, 0.5));
    light->setSpecular(osg::Vec4f(1.0, 1.0, 1.0, 1.0));
    light->setAmbient(osg::Vec4f(0.0, 0.0, 0.0, 1.0));
    lightsource = new osg::LightSource();
    lightsource->setLight(light);
    rootNode->addChild(lightsource);

    osg::StateSet* stateset = rootNode->getOrCreateStateSet();
    lightsource->setStateSetModes(*stateset, osg::StateAttribute::ON);*/
}

void Scene::run(double elapsed)
{
    ball->update(elapsed);
    text2d->update(elapsed);
    btVector3 velocity = ballBody->getVelocityInLocalPoint(btVector3(0, 0, 0));
    ballBody->setLinearVelocity(btVector3(velocity.x()/BALL_SLOW_SPEED,velocity.y(),velocity.z()));
    dynamicsWorld->stepSimulation(elapsed,10,1./120.);
}

\
