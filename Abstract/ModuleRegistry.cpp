#include "ModuleRegistry.h"

ModuleRegistry::ModuleRegistry() :
    playerReachedEnd(false)
{
}

void ModuleRegistry::registerWindow(SDLWindow *window)
{
    this->window = window;
}

SDLWindow *ModuleRegistry::getWindow()
{
    return window;
}

void ModuleRegistry::registerInputManager(InputManager *inputManager)
{
    this->inputManager = inputManager;
}

InputManager *ModuleRegistry::getInputManager()
{
    return inputManager;
}

void ModuleRegistry::registerRootNode(osg::MatrixTransform *rootNode)
{
    this->rootNode = rootNode;
}

osg::MatrixTransform *ModuleRegistry::getRootNode()
{
    return rootNode;
}

void ModuleRegistry::registerScene(Scene *scene)
{
    this->scene = scene;
}

Scene* ModuleRegistry::getScene()
{
    return scene;
}

void ModuleRegistry::registerSceneView(osgUtil::SceneView *sceneView)
{
    this->sceneView = sceneView;
}

osgUtil::SceneView *ModuleRegistry::getSceneView()
{
    return sceneView;
}

void ModuleRegistry::registerCamera(osg::ref_ptr<osg::Camera> camera)
{
    this->playerCamera = camera;
}

osg::ref_ptr<osg::Camera> ModuleRegistry::getCamera()
{
    return playerCamera;
}

void ModuleRegistry::registerDynamicsWorld(btDynamicsWorld *dynamicsWorld)
{
    this->dynamicsWorld = dynamicsWorld;
}

btDynamicsWorld *ModuleRegistry::getDynamicsWorld()
{
    return dynamicsWorld;
}

void ModuleRegistry::registerBall(Ball *ball)
{
    this->ball = ball;
}

Ball *ModuleRegistry::getBall()
{
    return ball;
}

void ModuleRegistry::registerLastCheckpoint(btVector3 *lastCheckpoint)
{
  this->lastCheckpoint = lastCheckpoint;
}
btVector3* ModuleRegistry::getLastCheckpoint()
{
  return lastCheckpoint;
}

void ModuleRegistry::registerText2D(Text2D *text2D)
{
  this->text2D = text2D;
}
Text2D* ModuleRegistry::getText2D()
{
  return text2D;
}

void ModuleRegistry::registerAllowMovement(bool *allowMovement)
{
    this->allowMovement = allowMovement;
}
bool* ModuleRegistry::getAllowMovement()
{
    return allowMovement;
}

void ModuleRegistry::registerCameraAngle(float *cameraAngle)
{
    this->cameraAngle = cameraAngle;
}
float* ModuleRegistry::getCameraAngle()
{
    return cameraAngle;
}