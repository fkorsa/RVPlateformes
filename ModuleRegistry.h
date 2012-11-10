#ifndef MODULEREGISTRY_H
#define MODULEREGISTRY_H

#include <osgUtil/SceneView>

class Window;
class InputManager;
class Ball;
class Scene;

class ModuleRegistry
{
public:
    ModuleRegistry();

    void registerWindow(Window *window);
    Window* getWindow();

    void registerInputManager(InputManager *inputManager);
    InputManager* getInputManager();

    void registerSceneView(osgUtil::SceneView *sceneView);
    osgUtil::SceneView* getSceneView();

    void registerScene(Scene *scene);
    Scene* getScene();

    void registerCamera(osg::ref_ptr<osg::Camera> camera);
    osg::ref_ptr<osg::Camera> getCamera();

private:
    Window *window;
    InputManager *inputManager;
    osgUtil::SceneView *sceneView;
    Scene *scene;
    Ball* ball;
    osg::ref_ptr<osg::Camera> playerCamera;
};

#endif // MODULEREGISTRY_H
