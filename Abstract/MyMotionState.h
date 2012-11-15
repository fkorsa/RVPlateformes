#ifndef MYMOTIONSTATE_H
#define MYMOTIONSTATE_H

#include <btBulletDynamicsCommon.h>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include "Utils.h"

class MyMotionState : public btMotionState
{
public:
    MyMotionState(osg::PositionAttitudeTransform *pat)
    {
        this->pat = pat;
        transform.setIdentity();
        transform.setOrigin(Utils::asBtVector3(pat->getPosition()));
        transform.setRotation(Utils::asBtQuaternion(pat->getAttitude()));
        mt = pat->asMatrixTransform();
        _com = osg::Vec3(0,0,0);
        _scale = osg::Vec3( 1., 1., 1. );
    }

    virtual void getWorldTransform(btTransform &worldTrans) const
    {
        worldTrans = transform;
    }
    virtual void setWorldTransform(const btTransform &worldTrans)
    {

        // transform is the model-to-world transformation used to place collision shapes
        // in the physics simulation. Bullet queries this with getWorldTransform().
        transform = worldTrans;

        // Compute the transformation of the OSG visual representation.
        const osg::Matrix dt = Utils::asOsgMatrix( worldTrans );

        // Accound for center of mass and scale.
        const osg::Vec3 cs( _com[0]*_scale[0], _com[1]*_scale[1], _com[2]*_scale[2] );
        const osg::Matrix csMat = osg::Matrix::translate( -cs );
        const osg::Matrix scale = osg::Matrix::scale( _scale );
        const osg::Matrix t = scale * csMat * dt;

        // LE PAT VEUT PAS FILER UNE MATRICE VALIDE
        // :/ AVEC LES MATRIX TRANSFORM CA DOIT SUREMENT MARCHER
        // IL EST 5H JE VAIS DODO
        if (mt.valid()) {
            mt->setMatrix(t);
        }
    }

private:
    osg::Vec3 _com, _scale;
    osg::ref_ptr< osg::MatrixTransform > mt;
    btTransform transform;
    osg::PositionAttitudeTransform *pat;
};

#endif // MYMOTIONSTATE_H
