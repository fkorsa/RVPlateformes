#include "ModuleRegistry.h"

ModuleRegistry::ModuleRegistry()
{
}

void ModuleRegistry::registerWindow(Window *window)
{
    this->window = window;
}

Window *ModuleRegistry::getWindow()
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

void ModuleRegistry::registerSceneView(osgUtil::SceneView *sceneView)
{
    this->sceneView = sceneView;
}

osgUtil::SceneView* ModuleRegistry::getSceneView()
{
    return sceneView;
}

void ModuleRegistry::registerScene(Scene *scene)
{
    this->scene = scene;
}

Scene* ModuleRegistry::getScene()
{
    return scene;
}

void ModuleRegistry::registerCamera(osg::ref_ptr<osg::Camera> camera)
{
    this->playerCamera = camera;
}

osg::ref_ptr<osg::Camera> ModuleRegistry::getCamera()
{
    return playerCamera;
}
