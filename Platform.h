#ifndef PLATFORM_H
#define PLATFORM_H

#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/Texture2D>

#include <osgbCollision/CollisionShapes.h>
#include <osgbCollision/RefBulletObject.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbDynamics/CreationRecord.h>

#include "ModuleRegistry.h"
#include "Constants.h"

class Platform
{
public:
    Platform(ModuleRegistry *moduleRegistry, const osg::Vec3& center, const osg::Vec3& lengths, float mass,
                                            osg::Texture2D* texture);
    void setTranlatingPlatformParameters(const osg::Vec3& originPoint, const osg::Vec3& endPoint, float movingSpeed);
    PlatformType getPlatformType();
    void update();
private:
    osg::MatrixTransform *matrixTransform;
    btRigidBody *body;
    PlatformType platformType;
    osg::Vec3 originPoint;
    osg::Vec3 endPoint;
    float movingSpeed;
};

#endif // PLATFORM_H
