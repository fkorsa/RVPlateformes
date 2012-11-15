#ifndef MODULEREGISTRY_H
#define MODULEREGISTRY_H

#include <osgUtil/SceneView>
#include <btBulletDynamicsCommon.h>

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

    void registerRootNode(osg::Group *rootNode);
    osg::Group* getRootNode();

    void registerScene(Scene *scene);
    Scene* getScene();

    void registerSceneView(osgUtil::SceneView *sceneView);
    osgUtil::SceneView* getSceneView();

    void registerCamera(osg::ref_ptr<osg::Camera> camera);
    osg::ref_ptr<osg::Camera> getCamera();

    void registerDynamicsWorld(btDynamicsWorld *dynamicsWorld);
    btDynamicsWorld* getDynamicsWorld();

    void registerBall(Ball *ball);
    Ball* getBall();

private:
    SDLWindow *window;
    InputManager *inputManager;
    Scene *scene;
    Ball* ball;
    osg::ref_ptr<osg::Camera> playerCamera;
    osg::Group *rootNode;
    osgUtil::SceneView *sceneView;
    btDynamicsWorld *dynamicsWorld;
};

#endif // MODULEREGISTRY_H
