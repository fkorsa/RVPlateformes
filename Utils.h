#ifndef UTILS_H
#define UTILS_H

#include <osg/Vec3f>
#include <osg/Quat>

#include <BulletDynamics/btBulletDynamicsCommon.h>

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

    // Convert a btTransform to an OSG Matrix
    static osg::Matrix asOsgMatrix( const btTransform& t )
    {
        btScalar ogl[ 16 ];
        t.getOpenGLMatrix( ogl );
        osg::Matrix m( ogl );
        return m;
    }

    static btTransform asBtTransform( const osg::Matrix& m )
    {
        const osg::Matrix::value_type* oPtr = m.ptr();
        btScalar bPtr[ 16 ];
        int idx;
        for (idx=0; idx<16; idx++)
            bPtr[ idx ] = oPtr[ idx ];
        btTransform t;
        t.setFromOpenGLMatrix( bPtr );
        return t;
    }


    static osg::Matrix asOsgMatrix( const btMatrix3x3& m )
    {
        btScalar f[ 9 ];
        m.getOpenGLSubMatrix( f );
        return( osg::Matrix(
            f[0], f[1], f[2], 0.,
            f[3], f[4], f[5], 0.,
            f[6], f[7], f[8], 0.,
            0., 0., 0., 1. ) );
    }

};

#endif // UTILS_H
