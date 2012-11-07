#ifndef MODULEREGISTRY_H
#define MODULEREGISTRY_H

#include <osgUtil/SceneView>

class Window;
class InputManager;
class Scene;

class ModuleRegistry
{
public:
    ModuleRegistry();

    void registerWindow(Window *window);
    Window* getWindow();

    void registerInputManager(InputManager *inputManager);
    InputManager* getInputManager();

    void registerSceneView(osg::ref_ptr<osgUtil::SceneView> sceneView);
    osg::ref_ptr<osgUtil::SceneView> getSceneView();

    void registerScene(Scene *scene);
    Scene* getScene();

    void registerCamera(osg::ref_ptr<osg::Camera> camera);
    osg::ref_ptr<osg::Camera> getCamera();

private:
    Window *window;
    InputManager *inputManager;
    osg::ref_ptr<osgUtil::SceneView> sceneView;
    Scene *scene;
    osg::ref_ptr<osg::Camera> playerCamera;
};

#endif // MODULEREGISTRY_H
