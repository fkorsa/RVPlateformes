#ifndef PLATFORM_H
#define PLATFORM_H

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
    Platform(ModuleRegistry *moduleRegistry, const osg::Vec3& center, const osg::Vec3& lengths, float mass,
                                            osg::Texture2D* texture);
    void setTranslatingPlatformParameters(const osg::Vec3& endPoint, float movingSpeed);
    void update(double elapsed);
    void movePlatform(osg::Vec3 movingVector);
private:
    btRigidBody *body;
    osgbDynamics::MotionState* shakeMotion;
    osg::Vec3 endPoint;
    osg::Vec3 startPoint;
    bool movesTowardEnd;
    bool isMovingPlatform;
    float movingSpeed;
};

#endif // PLATFORM_H
