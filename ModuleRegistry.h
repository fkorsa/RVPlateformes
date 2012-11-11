#ifndef MODULEREGISTRY_H
#define MODULEREGISTRY_H

#include <osgUtil/SceneView>

class SDLWindow;
class InputManager;
class Ball;
class Scene;

class ModuleRegistry
{
public:
    ModuleRegistry();

    void registerWindow(SDLWindow *window);
    SDLWindow* getWindow();

    void registerInputManager(InputManager *inputManager);
    InputManager* getInputManager();

    void registerRootNode(osg::MatrixTransform *rootNode);
    osg::MatrixTransform* getRootNode();

    void registerScene(Scene *scene);
    Scene* getScene();

    void registerSceneView(osgUtil::SceneView *sceneView);
    osgUtil::SceneView* getSceneView();

    void registerCamera(osg::ref_ptr<osg::Camera> camera);
    osg::ref_ptr<osg::Camera> getCamera();

private:
    SDLWindow *window;
    InputManager *inputManager;
    Scene *scene;
    Ball* ball;
    osg::ref_ptr<osg::Camera> playerCamera;
    osg::MatrixTransform *rootNode;
    osgUtil::SceneView *sceneView;
};

#endif // MODULEREGISTRY_H
