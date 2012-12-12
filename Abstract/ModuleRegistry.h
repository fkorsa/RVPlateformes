#ifndef MODULEREGISTRY_H
#define MODULEREGISTRY_H

#include <osgUtil/SceneView>
#include <btBulletDynamicsCommon.h>

class SDLWindow;
class InputManager;
class Ball;
class Scene;
class Text2D;
class Text3D;

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

    void registerDynamicsWorld(btDynamicsWorld *dynamicsWorld);
    btDynamicsWorld* getDynamicsWorld();

    void registerBall(Ball *ball);
    Ball* getBall();
    
    void registerLastCheckpoint(btVector3 *lastCheckpoint);
    btVector3* getLastCheckpoint();
    
    void registerText2D(Text2D *text2D);
    Text2D* getText2D();
    
    void registerText3D(Text3D *text3D);
    Text3D* getText3D();
    
    void registerAllowMovement(bool *allowMovement);
    bool* getAllowMovement();
    
    void registerCameraAngle(float *cameraAngle);
    float* getCameraAngle();
    
    bool playerReachedEnd;

private:
    SDLWindow *window;
    InputManager *inputManager;
    Scene *scene;
    Ball* ball;
    osg::ref_ptr<osg::Camera> playerCamera;
    osg::MatrixTransform *rootNode;
    osgUtil::SceneView *sceneView;
    btDynamicsWorld *dynamicsWorld;
    btVector3 *lastCheckpoint;
    Text2D *text2D;
    Text3D *text3D;
    bool *allowMovement;
    float *cameraAngle;
};

#endif // MODULEREGISTRY_H

