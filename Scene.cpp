#include "Scene.h"

#define VRJUGGLER

Scene::Scene() :
    numPlatforms(0), time_elapsed_lost(0),currentLevel(1),allowMovement(false),time_elapsed_begin(0),time_elapsed_end(0),
    cameraAngle(0), hasStartedEndText(false)
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
    
    moduleRegistry->registerAllowMovement(&allowMovement);
    moduleRegistry->registerCameraAngle(&cameraAngle);
    
    createLights();
    // SKYBOX !
    Skybox* skybox = new Skybox(rootNode,"skybox1");

    // 2D TEXT FOR DEBUGGING PURPOSE !
    text2d = new Text2D(rootNode);
    moduleRegistry->registerText2D(text2d);

    // 3D TEXT FOR FUN PURPOSE !
    text3d = new Text3D(rootNode);

    // THE MIGHTY BALL
    ball = new Ball(osg::Vec3f(0, 0, 50), 7., moduleRegistry);
    moduleRegistry->getInputManager()->setBall(ball);
    moduleRegistry->registerBall(ball);
    ball->setModuleRegistry(moduleRegistry);
    ballBody = ball->getBody();

    createLevel(currentLevel);

#ifndef VRJUGGLER
    moduleRegistry->getSceneView()->setSceneData(rootNode);
#endif
}



void Scene::createLights()
{
    // Add light
    osg::Light* light = new osg::Light();
    light->setLightNum(0);
    light->setPosition(osg::Vec4f(50.0, 0.0, 500, 1.0));
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
        text3d->setColor(osg::Vec4(1, 0, 0, 1));
        text3d->setText("Perdu !");
        if(time_elapsed_lost < 2)
        {
            time_elapsed_lost += elapsed;
            text3d->setPosition(textOffset-osg::Vec3f(0., 0., time_elapsed_lost*20));
        }
        else
        {
            text3d->setText("");
            resetLevel();
            createLevel(currentLevel);
            setBallPos(*lastCheckpoint);
            time_elapsed_lost = 0;
            cameraAngle = 0;
        }
    }
    else
    {
        osg::Matrix cameraMatrix;
        //cameraMatrix.makeLookAt(Utils::asOsgVec3(ballPos) + osg::Vec3f(-15*cos(cameraAngle), 15*sin(cameraAngle), 10), Utils::asOsgVec3(ballPos), osg::Vec3f(0, 0, 1));
        cameraMatrix.makeLookAt(Utils::asOsgVec3(ballPos) + osg::Vec3f(0, 0, 10), Utils::asOsgVec3(ballPos) + osg::Vec3f(15*cos(cameraAngle), -15*sin(cameraAngle), 10), osg::Vec3f(0, 0, 1));
        rootNode->setMatrix(cameraMatrix);
    }
    if(!allowMovement)
    {
        time_elapsed_begin += elapsed;
        text3d->setPosition(textOffset-osg::Vec3f(0, 0., time_elapsed_begin*20));
        if(time_elapsed_begin > 2)
        {
            allowMovement = true;
            time_elapsed_begin = 0;
            text3d->setText("");
        }
    }
    if(moduleRegistry->playerReachedEnd)
    {
        if(currentLevel == MAX_LEVEL)
        {
            if(!hasStartedEndText)
            {
                text3d->setText("THE END !");
                text3d->setColor(osg::Vec4d(0, 0, 1, 1));
                text3d->setPosition(textOffset);
                hasStartedEndText = true;
            }
            time_elapsed_end += elapsed;
            text3d->setPosition(textOffset-osg::Vec3f(0, 0., time_elapsed_end*20));
            if(time_elapsed_end > 2)
            {
                text3d->setText("");
                exit(0);
            }
        }
        else
        {
            setBallPos(btVector3(0, 0, 50));
            resetLevel();
            createLevel(++currentLevel);
            moduleRegistry->playerReachedEnd = false;
        }
    }
}

void Scene::resetLevel()
{
  int i;
  for(i=0; i<numPlatforms; i++)
  {
    delete platforms[i];
  }
  for(i=0; i<numPyramids; i++)
  {
    delete pyramids[i];
  }
}

void Scene::createLevel(int level)
{
    //load textures
    osg::Image* image;
    osg::Texture2D *texture1 = new osg::Texture2D, *texture3 = new osg::Texture2D, *texture2 = new osg::Texture2D;
    image = osgDB::readImageFile("data/textures/box1.jpg");
    texture1->setImage(image);
    image = osgDB::readImageFile("data/textures/box2.jpg");
    texture2->setImage(image);
    image = osgDB::readImageFile("data/textures/box3.jpg");
    texture3->setImage(image);
    
    numPlatforms = 0;
    numPyramids = 0;
    
    allowMovement = false;
    time_elapsed_begin = 0;
    std::stringstream out;
    out << level;
    text3d->setText("Level : " + out.str());
    text3d->setColor(osg::Vec4d(0, 1, 0, 1));
    text3d->setPosition(textOffset);
    switch(level)
    {
        case 1:
            //create platforms
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -5 ), osg::Vec3f(100, 100, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 110., 0., -5. ), osg::Vec3f(100, 100, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 225., 0., -5. ), osg::Vec3f(100, 100, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 345., 0., -5. ), osg::Vec3f(100, 100, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 345., 130., -5. ), osg::Vec3f(100, 100, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 485., 130., -5. ), osg::Vec3f(100, 100, 10), texture3))
                ->setUnstable(1);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 615., 130., -5. ), osg::Vec3f(100, 100, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 715., 130., -10. ), osg::Vec3f(100, 100, 10), texture3))
                ->setTranslatingPlatformParameters(btVector3(715, 130, 45), 20);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 815., 130., 45. ), osg::Vec3f(100, 100, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 815., 0., 45. ), osg::Vec3f(90, 90, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 815., -130., 45. ), osg::Vec3f(80, 80, 10), texture2))
                ->setLevelEnd();
            
            //create pyramids
            pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,10.0f,osg::Vec3(100,0,37),texture2);
            pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,10.0f,osg::Vec3(160,0,15),texture2); 
            break;
        case 2:
            //create platforms
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -5 ), osg::Vec3f(100, 100, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 110., 0., -5. ), osg::Vec3f(100, 100, 10), texture3))
                ->setLevelEnd();
            
            //create pyramids
            pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,10.0f,osg::Vec3(100,0,37),texture2);
            pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,10.0f,osg::Vec3(160,0,15),texture2); 
            break;
    }
}
void Scene::setBallPos(btVector3 ballNewPos)
{
    btVector3 ballPos = ball->getBody()->getWorldTransform().getOrigin(), platformPos;  
    ball->getBody()->setLinearVelocity(btVector3(0, 0, 0));
    ball->getBody()->translate(ballNewPos-ballPos);
}