#ifndef UTILS_H
#define UTILS_H

#include <osg/Vec3f>
#include <osg/Quat>

#include <bullet/btBulletDynamicsCommon.h>

class Utils
{
public:
    static btVector3 asBtVector3(osg::Vec3f vector)
    {
        return btVector3(vector.x(), vector.y(), vector.z());
    }

    static osg::Vec3f asOsgVec3(btVector3 vector)
    {
        return osg::Vec3f(vector.x(), vector.y(), vector.z());
    }

    static btQuaternion asBtQuaternion(osg::Quat quat)
    {
        return btQuaternion(quat.x(), quat.y(), quat.z(), quat.w());
    }

    static osg::Quat asOsgQuaternion(btQuaternion quat)
    {
        return osg::Quat(quat.x(), quat.y(), quat.z(), quat.w());
    }

};

#endif // UTILS_H
