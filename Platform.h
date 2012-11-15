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

class Platform
{
public:
    Platform(ModuleRegistry *moduleRegistry, const osg::Vec3& center, const osg::Vec3& lengths, osg::Texture2D *texture);
    Platform* setTranslatingPlatformParameters(const osg::Vec3& endPoint, float movingSpeed);
    Platform* setUnstable(float platformUnstability);
    Platform* setMass(float mass);
    Platform* setPositionElasticity(float elasticity = 300.0f, float resistance = 10.0f);
    void update(double elapsed);
    void movePlatform(osg::Vec3 movingVector);
    void rotatePlatform(float direction, float directionFactor);
private:
    ModuleRegistry* registry;
    btRigidBody *body;
    osgbDynamics::MotionState* shakeMotion;
    osg::PositionAttitudeTransform* platformPAT;
    osg::Vec3f endPoint;
    osg::Vec3f startPoint;
    osg::Vec3f desiredCurrentPos, currentPos;
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
