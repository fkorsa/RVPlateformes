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

#include "../Text2d.h"

#include "../Abstract/ModuleRegistry.h"
#include "../Constants.h"
#include "Ball.h"
#include "../Abstract/MyMotionState.h"
#include "../Utils.h"

class Platform
{
public:
    Platform(ModuleRegistry *moduleRegistry, const osg::Vec3f &center, const osg::Vec3f &lengths, osg::Texture2D *texture);
    ~Platform();
    Platform* setTranslatingPlatformParameters(const btVector3& endPoint, float movingSpeedTowardEnd, float movingSpeedTowardStart);
    Platform* setUnstable(float platformUnstability);
    Platform* setMass(float mass);
    Platform* setPositionElasticity(float elasticity = 300.0f, float resistance = 1.0f);
    Platform* setCheckpoint();
    Platform* setLevelEnd();
    Platform* setAngle(btVector3 direction, float angle);
    void update(double elapsed);
private:
    void movePlatform(btVector3 movingVector);
    void rotatePlatform(float direction, float directionFactor);
    
    bool ballWasHereRecently;
    float timeSinceLastContact;
    ModuleRegistry* registry;
    btRigidBody *body;
    MyMotionState* platformMotionState;
    osg::ref_ptr<osg::MatrixTransform> platformMT;
    btVector3 endPoint;
    btVector3 startPoint;
    btVector3 desiredCurrentPos, currentPos;
    btVector3 *lastCheckpoint;
    bool movesTowardEnd;
    bool isPlatformMoving, isUnstable, isElastic, isFalling, isCheckpoint, isLevelEnd;
    float movingSpeedTowardEnd, movingSpeedTowardStart;

    // Variables used for unstable platforms
    float directionDelta, rotatingDirection, directionFactor, platformUnstability;

    // Variables used for oscillating platforms
    float positionElasticity,positionResistance;
};

#endif // PLATFORM_H
