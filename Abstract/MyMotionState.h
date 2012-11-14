#ifndef MYMOTIONSTATE_H
#define MYMOTIONSTATE_H

#include <btBulletDynamicsCommon.h>

#include <osg/PositionAttitudeTransform>

#include "Utils.h"

class MyMotionState : public btMotionState
{
public:
    MyMotionState(osg::PositionAttitudeTransform *pat)
    {
        this->pat = pat;
    }

    virtual void getWorldTransform(btTransform &worldTrans) const
    {
        worldTrans.setIdentity();
        worldTrans.setOrigin(Utils::asBtVector3(pat->getPosition()));
        worldTrans.setRotation(Utils::asBtQuaternion(pat->getAttitude()));
    }
    virtual void setWorldTransform(const btTransform &worldTrans)
    {
        pat->setAttitude(Utils::asOsgQuaternion(worldTrans.getRotation()));
        pat->setPosition(Utils::asOsgVec3(worldTrans.getOrigin()));
    }

private:
    osg::PositionAttitudeTransform *pat;
};

#endif // MYMOTIONSTATE_H
