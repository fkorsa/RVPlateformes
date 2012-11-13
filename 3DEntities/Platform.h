#ifndef PLATFORM_H
#define PLATFORM_H

#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/Math>

#include <osgbCollision/CollisionShapes.h>
#include <osgbCollision/RefBulletObject.h>
#include <osgbCollision/Utils.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbDynamics/CreationRecord.h>
#include <osgbDynamics/MotionState.h>

#include "ModuleRegistry.h"
#include "Constants.h"
#include "Ball.h"

#include "Utils.h"

class Platform
{
public:
    Platform(ModuleRegistry *moduleRegistry, const osg::Vec3f &center, const osg::Vec3f &lengths, osg::Texture2D *texture);
    Platform* setTranslatingPlatformParameters(const btVector3& endPoint, float movingSpeed);
    Platform* setUnstable(float platformUnstability);
    Platform* setMass(float mass);
    Platform* setPositionElasticity(float elasticity = 300.0f, float resistance = 10.0f);
    void update(double elapsed);
    void movePlatform(btVector3 movingVector);
    void rotatePlatform(float direction, float directionFactor);
private:
    ModuleRegistry* registry;
    btRigidBody *body;
    osgbDynamics::MotionState* shakeMotion;
    osg::PositionAttitudeTransform* platformPAT;
    btVector3 endPoint;
    btVector3 startPoint;
    btVector3 desiredCurrentPos, currentPos;
    bool movesTowardEnd;
    bool isPlatformMoving, isUnstable;
    float movingSpeed;

    // Variables used for unstable platforms
    float directionDelta, rotatingDirection, directionFactor, platformUnstability;
    bool firstRotateDirection;

    // Variables used for oscillating platforms
    float positionElasticity,positionResistance;
};

#endif // PLATFORM_H
