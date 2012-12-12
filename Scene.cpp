#include "Scene.h"

#define VRJUGGLER

Scene::Scene() :
    numPlatforms(0), time_elapsed_lost(0),currentLevel(0),allowMovement(false),time_elapsed_begin(0),time_elapsed_end_level(0),time_elapsed_end_game(0),
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
    solver->reset();

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
    moduleRegistry->registerText3D(text3d);

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
    if(elapsed>10000000)
      elapsed = 0.016;
    dynamicsWorld->stepSimulation(elapsed,10,1./120.);
    btVector3 ballPos = ball->getBody()->getWorldTransform().getOrigin();
    std::stringstream out;
    out << "ball pos : " << ballPos.x();
    *(moduleRegistry->getText2D()->print()) = out.str();
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
        cameraMatrix.makeLookAt(Utils::asOsgVec3(ballPos) + osg::Vec3f(-20*cos(cameraAngle), 20*sin(cameraAngle), 10), Utils::asOsgVec3(ballPos) + osg::Vec3f(0, 0, 10), osg::Vec3f(0, 0, 1));
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
        time_elapsed_end_level += elapsed;
        if(currentLevel == MAX_LEVEL)
        {
            time_elapsed_end_game += elapsed;
            if(!hasStartedEndText)
            {
                text3d->setText("THE END !");
                text3d->setColor(osg::Vec4d(0, 0, 1, 1));
                text3d->setPosition(textOffset);
                hasStartedEndText = true;
            }
            text3d->setPosition(textOffset-osg::Vec3f(0, 0., time_elapsed_end_game*20));
            if(time_elapsed_end_game > 2)
            {
                text3d->setText("");
                exit(0);
            }
        }
        else
        {
            if(!hasStartedEndText)
            {
                std::stringstream out;
                out << currentLevel;
                text3d->setText("You reached the end of level " + out.str() + " !");
                text3d->setColor(osg::Vec4d(0, 1, 1, 1));
                text3d->setPosition(textOffset);
                hasStartedEndText = true;
            }
            text3d->setPosition(textOffset-osg::Vec3f(0, 0., time_elapsed_end_level*20));
            if(time_elapsed_end_level > 2)
            {
                moduleRegistry->playerReachedEnd = false;
                setBallPos(btVector3(0, 0, 50));
                cameraAngle = 0;
                resetLevel();
                createLevel(++currentLevel);
            }
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

        case 0:
            //create platforms
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -5 ), osg::Vec3f(800, 800, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 460., 0., -5. ), osg::Vec3f(80, 80, 10), texture2))
                ->setPositionElasticity(0.2f,0.0f)
                ->setLevelEnd();
                
                
            pyramids[numPyramids++] = new Pyramid(moduleRegistry,6,2,20,0.3f,osg::Vec3(0,200,-5),texture2);    
            pyramids[numPyramids++] = new Pyramid(moduleRegistry,6,2,20,0.3f,osg::Vec3(0,-200,-5),texture2);        
                
            break;
        
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
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 615., 130., -5. ), osg::Vec3f(100, 100, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 715., 130., -10. ), osg::Vec3f(100, 100, 10), texture3))
                ->setTranslatingPlatformParameters(btVector3(715, 130, 45), 20, 20);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 815., 130., 45. ), osg::Vec3f(100, 100, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 815., 0., 45. ), osg::Vec3f(90, 90, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 815., -130., 45. ), osg::Vec3f(80, 80, 10), texture2))
                ->setLevelEnd();
            break;
        case 2:
            //create platforms
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -5 ), osg::Vec3f(80, 80, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 110., 0., -5. ), osg::Vec3f(80, 80, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 230., 0., -5. ), osg::Vec3f(80, 80, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 310., 0., -5. ), osg::Vec3f(80, 80, 10), texture3))
                ->setTranslatingPlatformParameters(btVector3(350, 0, -5), 20, 20)
                ->setUnstable(0.4);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 430., 0., -5. ), osg::Vec3f(80, 80, 10), texture1))
                ->setCheckpoint();
            
            //left path
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 480., 100., -5. ), osg::Vec3f(30, 30, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 565., 100., 5 ), osg::Vec3f(80, 80, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 625., 100., 25 ), osg::Vec3f(80, 80, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 705., 100., 45 ), osg::Vec3f(80, 80, 10), texture3));
            
            //right path
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 430., -120., -5. ), osg::Vec3f(80, 80, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 550., -120., -5. ), osg::Vec3f(60, 60, 10), texture3))
                ->setTranslatingPlatformParameters(btVector3(550, -120, 40), 30, 30);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 640., -120., 75 ), osg::Vec3f(60, 60, 10), texture3))
                ->setTranslatingPlatformParameters(btVector3(640, -120, 30), 30, 30);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 725., -120., 75 ), osg::Vec3f(80, 80, 10), texture3));
            
            //middle path
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 725., 0., 65 ), osg::Vec3f(80, 80, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 835., 0., 85 ), osg::Vec3f(80, 80, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 935., 0., 105 ), osg::Vec3f(80, 80, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 1025., 0., 120 ), osg::Vec3f(80, 80, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 1155., 0., 120 ), osg::Vec3f(80, 80, 10), texture2))
                ->setLevelEnd();
            
            //create pyramids
            //pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,10.0f,osg::Vec3(100,0,37),texture2);
            break;
        case 3:
            //create platforms
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -5 ), osg::Vec3f(60, 60, 10), texture1))
                ->setCheckpoint()
                ->setUnstable(0.5);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 90, 0., -5 ), osg::Vec3f(60, 60, 10), texture3))
                ->setPositionElasticity(1500, 1);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 180, 0., -5 ), osg::Vec3f(60, 60, 10), texture3))
                ->setUnstable(0.5);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 270, 0., -5 ), osg::Vec3f(60, 60, 10), texture3))
                ->setAngle(btVector3(0, 1, 0), -0.4)
                ->setUnstable(0.5);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 320, 0., -5 ), osg::Vec3f(60, 60, 10), texture3))
                ->setAngle(btVector3(0, 1, 0), 0.4)
                ->setUnstable(0.5);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 380, 0., -18 ), osg::Vec3f(60, 60, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 455, 0., 7 ), osg::Vec3f(100, 60, 10), texture3))
                ->setAngle(btVector3(0, 1, 0), -0.5)
                ->setUnstable(0.5);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 540, 0., 7 ), osg::Vec3f(100, 60, 10), texture3))
                ->setAngle(btVector3(0, 1, 0), 0.5)
                ->setUnstable(0.5);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 645, 0., 0 ), osg::Vec3f(60, 60, 10), texture2))
                ->setLevelEnd();
            
            // elasticity, resistance      
                //->setPositionElasticity(1500, 1);
            //create pyramids
            // width, depth, size, mass, center
            pyramids[numPyramids++] = new Pyramid(moduleRegistry,2,3,10,1.0f,osg::Vec3(90,0,-5),texture2);
//             pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,100.0f,osg::Vec3(600,0,75),texture2);
            break;
            
        case 4: 
            //create platforms
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -5 ), osg::Vec3f(40, 40, 10), texture1))
                ->setCheckpoint()
                ->setUnstable(0.5);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 90, 0., -5 ), osg::Vec3f(40, 40, 10), texture3))
                ->setUnstable(0.5);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 180, 0., -5 ), osg::Vec3f(40, 40, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 1000, 0., -5 ), osg::Vec3f(40, 40, 10), texture3))
                ->setTranslatingPlatformParameters(btVector3(220, 0., -5), 40, 40);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 300, -20., 5 ), osg::Vec3f(40, 5, 5), texture3))
                ->setTranslatingPlatformParameters(btVector3(300, 20, 5), 40, 40);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 420, -20., 5 ), osg::Vec3f(40, 5, 5), texture3))
                ->setTranslatingPlatformParameters(btVector3(420, 20, 5), 40, 40);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 540, -20., 5 ), osg::Vec3f(40, 5, 5), texture3))
                ->setTranslatingPlatformParameters(btVector3(540, 20, 5), 50, 50);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 660, -20., 5 ), osg::Vec3f(40, 5, 5), texture3))
                ->setTranslatingPlatformParameters(btVector3(660, 20, 5), 60, 60);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 1000, 0., 5 ), osg::Vec3f(10, 10, 10), texture2))
                ->setLevelEnd();
            break;
            
        case 5: 
            //create platforms
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 0., 0., -5 ), osg::Vec3f(40, 40, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 90, 0., -5 ), osg::Vec3f(40, 40, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 180, 0., -5 ), osg::Vec3f(40, 40, 10), texture3));
            
            //left path
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 180, 90., 5 ), osg::Vec3f(40, 40, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 240, 90., 5 ), osg::Vec3f(40, 40, 10), texture3))
                ->setTranslatingPlatformParameters(btVector3(340, 180., 105), 30, 40);
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 400, 180., 105 ), osg::Vec3f(40, 40, 10), texture1))
                ->setCheckpoint();
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 400, 255., 105 ), osg::Vec3f(30, 30, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 475, 255., 85 ), osg::Vec3f(20, 20, 10), texture3));
            platforms[numPlatforms++] = (new Platform(moduleRegistry,osg::Vec3f( 475, 310., 85 ), osg::Vec3f(10, 10, 10), texture2))
                ->setLevelEnd();
            
            // elasticity, resistance      
                //->setPositionElasticity(1500, 1);
            //create pyramids
            // width, depth, size, mass, center
            pyramids[numPyramids++] = new Pyramid(moduleRegistry,2,2,3,0.9f,osg::Vec3(90,0,-5),texture2);
//             pyramids[numPyramids++] = new Pyramid(moduleRegistry,1,1,7,100.0f,osg::Vec3(600,0,75),texture2);
            break;
    }
}
void Scene::setBallPos(btVector3 ballNewPos)
{
    btVector3 ballPos = ball->getBody()->getWorldTransform().getOrigin();  
    ball->getBody()->setLinearVelocity(btVector3(0, 0, 0));
    ball->getBody()->translate(ballNewPos-ballPos);
}