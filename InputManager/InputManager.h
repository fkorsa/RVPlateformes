#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Module.h"
#include "Constants.h"
#include "Ball.h"

#include <osg/Math>
#include <QDebug>

class InputManager : public Module
{
public:
    InputManager();
<<<<<<< HEAD

=======
    // Mouvement godmode
>>>>>>> 6c72a4272753d75b8450a56c567c20ab635291c1
    void walk(WalkingDirection dir, float distance);
    void rotateCamera(CameraDirection dir, float angle);

    // Pour replacer la caméra quand on repasse en !godmode
    void resetCameraToGameMode();

    // Déplace la balle
    void moveLeft();
    void moveRight();
    void jump();

    void setBall(Ball* _ball);

private:

    Ball* ball;


};

#endif // INPUTMANAGER_H
