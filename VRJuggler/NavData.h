#ifndef NAVDATA_H
#define NAVDATA_H

#ifdef VRJUGGLER

#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <osg/MatrixTransform>
#include <vpr/IO/SerializableObject.h>
#include <vpr/IO/ObjectReader.h>
#include <vpr/IO/ObjectWriter.h>
#include <plugins/ApplicationDataManager/UserData.h>

class NavData : public vpr::SerializableObject
{
public:
    virtual vpr::ReturnStatus readObject(vpr::ObjectReader* reader)
    {
        float pos_data[16];
        for ( unsigned n=0;n<16;n++ )
        {
            pos_data[n] = reader->readFloat();
        }

        mCurPos.set(pos_data);
        return vpr::ReturnStatus::Succeed;
    }

    virtual void writeObject(vpr::ObjectWriter* writer)
    {
        const float* pos_data = mCurPos.getData();
        for ( int n=0;n<16;n++ )
        {
            writer->writeFloat(pos_data[n]);
        }
        return;
    }
public:
    gmtl::Matrix44f mCurPos;      /**< Current position */
};

#endif // VRJUGGLER
#endif // NAVDATA_H
