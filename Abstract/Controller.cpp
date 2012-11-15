#include "Controller.h"

//#define VRJUGGLER

Controller::Controller(int argc, char *argv[])
{    
    ModuleRegistry moduleRegistry;

#ifdef VRJUGGLER
    vrj::Kernel* kernel = vrj::Kernel::instance();
    OsgNav *application = new OsgNav(kernel, argc, argv);

    if ( argc <= 1 )
    {
        std::cout << "\n\nUsage: " << argv[0]
                  << " vjconfigfile\n\n";
        return;
    }

    for (int i = 1; i < argc; ++i)
    {
        kernel->loadConfigFile(argv[i]);
    }

    kernel->start();

    kernel->setApplication(application);
#else
    int loopCnt = 0;
    window = new SDLWindow(&moduleRegistry);
    moduleRegistry.registerWindow(window);
    window->setModuleRegistry(&moduleRegistry);
    moduleRegistry.registerRootNode(new osg::MatrixTransform);

    inputStrategy = new SDLInputStrategy();
    inputStrategy->setModuleRegistry(&moduleRegistry);
#endif // VRJUGGLER

    inputManager = new InputManager();
    moduleRegistry.registerInputManager(inputManager);
    inputManager->setModuleRegistry(&moduleRegistry);

    scene = new Scene();
    moduleRegistry.registerScene(scene);
    scene->setModuleRegistry(&moduleRegistry);

#ifdef VRJUGGLER
    application->setModuleRegistry(&moduleRegistry);
    kernel->waitForKernelStop();
#else
    scene->createScene();
    while(true)
    {
        if(inputStrategy->handleInput() == RETURN_EXIT)
        {
            break;
        }
        currentTime = osgTimer.tick();
        double elapsed = osgTimer.delta_s(previousTime, currentTime);
        scene->run(elapsed);
        previousTime = currentTime;
        window->draw();
        if(loopCnt<3)
        {
            loopCnt++;
            moduleRegistry.getCamera()->setViewMatrixAsLookAt(osg::Vec3(140, -400, 50),
                                                               osg::Vec3(140, 0, 50),
                                                               osg::Vec3(0, 0, 1));
        }
    }
#endif //VRJUGGLER
}
