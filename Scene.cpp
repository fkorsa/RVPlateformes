#include "Scene.h"

//#define VRJUGGLER

Scene::Scene() :
    numPlatforms(0)
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
    dynamicsWorld->setGravity( btVector3( 0, 0, -250 ) );

    return( dynamicsWorld );
}

void Scene::createScene()
{
    rootNode = moduleRegistry->getRootNode();

    moduleRegistry->registerDynamicsWorld(dynamicsWorld);

    createLights();
    // SKYBOX !
    Skybox* skybox = new Skybox(rootNode,"skybox1");

    // 2D TEXT FOR DEBUGGING PURPOSE !
    text2d = new Text2D(rootNode);

    // 3D TEXT FOR FUN PURPOSE !
    //text3d = new Text3D(rootNode);

    // THE MIGHTY BALL
    ball = new Ball(osg::Vec3f(0, 0, 20), 7., moduleRegistry);
    moduleRegistry->getInputManager()->setBall(ball);
    moduleRegistry->registerBall(ball);
    ballBody = ball->getBody();

    // LEVEL 1
    osg::Image* image1 = osgDB::readImageFile("data/textures/box3.jpg");
    osg::Texture2D* texture1 = new osg::Texture2D;
    texture1->setImage(image1);

    platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -25. ), osg::Vec3f(30, 30, 5), texture1))
            //->setPositionElasticity(2000.f,300.0f);
            ->setTranslatingPlatformParameters(btVector3(0., 0, -5), 10)
            //->setUnstable(10)
            ;
    platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 60., 0., -15. ), osg::Vec3(30, 30, 5), texture1))
            //->setPositionElasticity()
            ->setUnstable(1)
            ;
    platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 100., 0., 10. ), osg::Vec3(30, 30, 5), texture1))
            ->setPositionElasticity(260.f,4.0f);
    platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 160., 0., 5. ), osg::Vec3(50, 50, 5), texture1))
            ->setPositionElasticity(2600.f,400.0f);

    // SOME BOXES
    osg::Image* image2 = osgDB::readImageFile("data/textures/box2.jpg");
    osg::Texture2D* texture2 = new osg::Texture2D;
    texture2->setImage(image2);
    new Pyramid(moduleRegistry,1,1,7,10.0f,osg::Vec3(100,0,37),texture2);
    new Pyramid(moduleRegistry,4,4,7,10.0f,osg::Vec3(160,0,15),texture2);

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
}

void Scene::run(double elapsed)
{
    ball->update(elapsed);
    text2d->update(elapsed);
    //text3d->update(elapsed);
    for(int i = 0;i<numPlatforms;i++)
    {
        platforms[i]->update(elapsed);
    }
    if(elapsed>1)
      elapsed = 0.016;
    dynamicsWorld->stepSimulation(elapsed,10,1./120.);
  
}
