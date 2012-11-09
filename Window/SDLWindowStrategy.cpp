#include "SDLWindowStrategy.h"

SDLWindowStrategy::SDLWindowStrategy(ModuleRegistry *moduleRegistry)
{
    //SDL init
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_SetVideoMode(1280, 1024, 0, SDL_OPENGL);

    //OSG init
    sceneView = new osgUtil::SceneView();
    sceneView->setDefaults();
    sceneView->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);

    osg::ref_ptr<osg::Camera> playerCamera = sceneView->getCamera();
    playerCamera->setViewport(0, 0, 1280, 1024);
    playerCamera->setProjectionMatrixAsPerspective(45.0, playerCamera->getViewport()->aspectRatio(), 0.1, 1000.0);
    playerCamera->setClearColor(osg::Vec4(0.2, 0.2, 0.4, 0.0));
    sceneView->init();

    moduleRegistry->registerSceneView(sceneView);
    moduleRegistry->registerCamera(playerCamera);
}

void SDLWindowStrategy::draw()
{
    sceneView->update();
    sceneView->cull();
    sceneView->draw();
    SDL_GL_SwapBuffers();
}
