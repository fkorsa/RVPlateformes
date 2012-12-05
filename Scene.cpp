#include "Scene.h"

#define VRJUGGLER

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

    lastCheckpoint = new btVector3();
    moduleRegistry->registerLastCheckpoint(lastCheckpoint);
    
    createLights();
    // SKYBOX !
    Skybox* skybox = new Skybox(rootNode,"skybox1");

    // 2D TEXT FOR DEBUGGING PURPOSE !
    text2d = new Text2D(rootNode);

    // 3D TEXT FOR FUN PURPOSE !
    //text3d = new Text3D(rootNode);

    // THE MIGHTY BALL
    ball = new Ball(osg::Vec3f(550, 0, 170), 7., moduleRegistry);
    moduleRegistry->getInputManager()->setBall(ball);
    moduleRegistry->registerBall(ball);
    ballBody = ball->getBody();

    createPlatforms();

    createPyramids();

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
    btVector3 ballPos = ball->getBody()->getWorldTransform().getOrigin();
    if(ballPos.z() < -100)
    {
	resetLevel();
    }
    osg::Matrix cameraMatrix;
    cameraMatrix.makeLookAt(osg::Vec3f(ballPos.x() - 10, ballPos.y(), ballPos.z() + 50), Utils::asOsgVec3(ballPos), osg::Vec3f(1, 0, 0));
    rootNode->setMatrix(cameraMatrix);
}

void Scene::resetLevel()
{
  int i;
  btVector3 ballPos = ball->getBody()->getWorldTransform().getOrigin(), platformPos;  
  ball->getBody()->setLinearVelocity(btVector3(0, 0, 0));
  ball->getBody()->translate(*lastCheckpoint-ballPos);
  for(i=0; i<numPlatforms; i++)
  {
    delete platforms[i];
  }
  for(i=0; i<numPyramids; i++)
  {
    delete pyramids[i];
  }
  createPlatforms();
  createPyramids();
}

void Scene::createPlatforms()
{
 numPlatforms = 0;
 // LEVEL 1
    osg::Image* image;
    osg::Texture2D *texture1 = new osg::Texture2D, *texture3 = new osg::Texture2D, *texture2 = new osg::Texture2D;
    image = osgDB::readImageFile("data/textures/box1.jpg");
    texture1->setImage(image);
    image = osgDB::readImageFile("data/textures/box2.jpg");
    texture2->setImage(image);
    image = osgDB::readImageFile("data/textures/box3.jpg");
    texture3->setImage(image);
 platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -25. ), osg::Vec3f(30, 30, 5), texture1))
	  ->setCheckpoint();
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 60., 0., -15. ), osg::Vec3(30, 30, 5), texture2));
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 100., 0., 10. ), osg::Vec3(30, 30, 5), texture3))
	  ->setPositionElasticity(260.f,4.0f);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 160., 0., 5. ), osg::Vec3(50, 50, 5), texture2))
	  ->setPositionElasticity(2600.f,400.0f);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 220, 0., 10 ), osg::Vec3(50, 50, 5), texture3))
	  ->setUnstable(0.1);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 300, 0., 15 ), osg::Vec3(30, 30, 5), texture2))
	  ->setUnstable(0.2); 
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 360, 0., 15 ), osg::Vec3(20, 20, 5), texture1))
  ->setCheckpoint();
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 420, 0., 15 ), osg::Vec3(20, 20, 5), texture2))
	  ->setPositionElasticity(260.f,4.0f);;
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 480, 0., -10 ), osg::Vec3(20, 20, 5), texture3))
	  ->setTranslatingPlatformParameters(btVector3(480, 0, 70), 30);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 550, 0., 70 ), osg::Vec3(30, 30, 5), texture2));
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 610, 0., 70 ), osg::Vec3(30, 30, 5), texture3))
	  ->setUnstable(0.01)
	  ->setTranslatingPlatformParameters(btVector3(610, 0, 0), 30);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 870, 0., 0 ), osg::Vec3(400, 30, 5), texture2))
	  ->setCheckpoint();
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 700, -80, 75), osg::Vec3(50, 50, 150), texture3))
	  ->setTranslatingPlatformParameters(btVector3(700, 80, 75), 50);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 800, -20, 30), osg::Vec3(50, 5, 50), texture3))
	  ->setTranslatingPlatformParameters(btVector3(800, 20, 30), 20);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 880, -20, 30), osg::Vec3(50, 5, 50), texture3))
	  ->setTranslatingPlatformParameters(btVector3(880, 20, 30), 30);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 930, 20, 30), osg::Vec3(50, 5, 50), texture3))
	  ->setTranslatingPlatformParameters(btVector3(930, -20, 30), 20);
  platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3( 1020, 0, -100), osg::Vec3(50, 50, 5), texture3))
	  ->setTranslatingPlatformParameters(btVector3(1020, 0, 20), 400);
}

void Scene::createPyramids()
{
 // SOME BOXES
    numPyramids = 0;
    osg::Image* image2 = osgDB::readImageFile("data/textures/box2.jpg");
    osg::Texture2D* texture2 = new osg::Texture2D;
    texture2->setImage(image2);
    pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,10.0f,osg::Vec3(100,0,37),texture2);
    pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,10.0f,osg::Vec3(160,0,15),texture2); 
}