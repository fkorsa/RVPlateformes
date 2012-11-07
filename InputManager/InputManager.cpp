#include "InputManager.h"

InputManager::InputManager()
{
}

void InputManager::walk(Direction dir, float distance)
{
    osg::ref_ptr<osg::Camera> playerCamera = moduleRegistry->getCamera();
    osg::Vec3f eye, center, up;
    playerCamera->getViewMatrixAsLookAt(eye, center, up);
    switch(dir)
    {
        case LEFT:
            eye += osg::Vec3f(-distance, 0, 0);
            center += osg::Vec3f(-distance, 0, 0);
            break;
        case RIGHT:
            eye += osg::Vec3f(distance, 0, 0);
            center += osg::Vec3f(distance, 0, 0);
            break;
        case FRONT:
            eye += osg::Vec3f(0, distance, 0);
            center += osg::Vec3f(0, distance, 0);
            break;
        case BEHIND:
            eye += osg::Vec3f(0, -distance, 0);
            center += osg::Vec3f(0, -distance, 0);
            break;
    }
    playerCamera->setViewMatrixAsLookAt(eye, center, up);
}
