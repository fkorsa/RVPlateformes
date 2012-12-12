#include "InputManager.h"

InputManager::InputManager()
{
}

void InputManager::setBall(Ball* _ball)
{
    ball = _ball;
}

void InputManager::moveLeft()
{
    ball->moveLeft();
}

void InputManager::moveRight()
{
    ball->moveRight();
}

void InputManager::moveFront(float force)
{
    ball->moveFront(force);
}
  
void InputManager::moveBehind(float force)
{
    ball->moveBehind(force);
}

void InputManager::jump()
{
    ball->jump();
}


void InputManager::walk(WalkingDirection dir, float distance)
{
    osg::ref_ptr<osg::Camera> playerCamera = moduleRegistry->getCamera();
    osg::Vec3f eye, center, up, cameraDir, baseThirdVector, EC;
    playerCamera->getViewMatrixAsLookAt(eye, center, up);
    EC = center - eye;
    baseThirdVector = EC^up;
    switch(dir)
    {
        case WALKING_PARALLEL:
            center += baseThirdVector*distance;
            eye += baseThirdVector*distance;
            break;
        case WALKING_FRONT:
            center += EC*distance;
            eye += EC*distance;
            break;
    }
    cameraDir = center - eye;
    cameraDir.normalize();
    center = cameraDir + eye;
    playerCamera->setViewMatrixAsLookAt(eye, center, up);
}

void InputManager::rotateCamera(CameraDirection dir, float angle)
{
    osg::ref_ptr<osg::Camera> playerCamera = moduleRegistry->getCamera();
    osg::Vec3f eye, center, up, cameraDir, baseThirdVector, EC;
    osg::Vec3::value_type angleCosinus = cos(angle), angleSinus = sin(angle);
    playerCamera->getViewMatrixAsLookAt(eye, center, up);
    EC = center - eye;
    EC.normalize();
    up.normalize();
    baseThirdVector = EC^up;
    switch(dir)
    {
        case CAMERA_DIRECTION_X:
            center = EC*angleCosinus + baseThirdVector*angleSinus + eye;
            break;
        case CAMERA_DIRECTION_Y:
            center = EC*angleCosinus - up*angleSinus + eye;
            up = up*angleCosinus - EC*angleSinus;
            break;
    }
    cameraDir = center - eye;
    cameraDir.normalize();
    center = cameraDir + eye;
    up.normalize();
    playerCamera->setViewMatrixAsLookAt(eye, center, up);
}

void InputManager::resetCameraToGameMode()
{

}
