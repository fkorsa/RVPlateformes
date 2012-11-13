#ifndef PLATFORM_H
#define PLATFORM_H

#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

#include <osgbCollision/CollisionShapes.h>
#include <osgbCollision/RefBulletObject.h>
#include <osgbCollision/Utils.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbDynamics/CreationRecord.h>
#include <osgbDynamics/MotionState.h>

#include "ModuleRegistry.h"
#include "Constants.h"

class Platform
{
public:
    Platform(ModuleRegistry *moduleRegistry, const osg::Vec3& center, const osg::Vec3& lengths, osg::Texture2D *texture);
    Platform* setTranslatingPlatformParameters(const osg::Vec3& endPoint, float movingSpeed);
    Platform* setUnstable();
    Platform* setMass(float mass);
    void update(double elapsed);
    void movePlatform(osg::Vec3 movingVector);
    void rotatePlatform(float angle);
private:
    btRigidBody *body;
    osgbDynamics::MotionState* shakeMotion;
    osg::PositionAttitudeTransform* platformPAT;
    osg::Vec3 endPoint;
    osg::Vec3 startPoint;
    osg::Vec3 desiredCurrentPos, currentPos;
    bool movesTowardEnd;
    bool isPlatformMoving, isUnstable;
    bool firstRotateDirection;
    float movingSpeed;
    float rotatingAngle;
};

#endif // PLATFORM_H
