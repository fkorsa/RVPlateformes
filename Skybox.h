/* FROM: OpenSceneGraph example, osgvertexprogram.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*  THE SOFTWARE.
*/

#ifndef SKYBOX_H
#define SKYBOX_H

#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Transform>
#include <osg/Material>
#include <osg/NodeCallback>
#include <osg/Depth>
#include <osg/CullFace>
#include <osg/TexMat>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osg/TexEnvCombine>
#include <osg/TextureCubeMap>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/CullVisitor>

class Skybox
{
public:
    Skybox(osg::Group *rootNode);

private:
    osg::TextureCubeMap* readCubeMap();
    osg::Node* createSkyBox();

    class MoveEarthySkyWithEyePointTransform : public osg::Transform
    {
    public:
        /** Get the transformation matrix which moves from local coords to world coords.*/
        virtual bool computeLocalToWorldMatrix(osg::Matrix& matrix,osg::NodeVisitor* nv) const
        {
            osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
            if (cv)
            {
                osg::Vec3 eyePointLocal = cv->getEyeLocal();
                matrix.preMultTranslate(eyePointLocal);
            }
            return true;
        }

        /** Get the transformation matrix which moves from world coords to local coords.*/
        virtual bool computeWorldToLocalMatrix(osg::Matrix& matrix,osg::NodeVisitor* nv) const
        {
            osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
            if (cv)
            {
                osg::Vec3 eyePointLocal = cv->getEyeLocal();
                matrix.postMultTranslate(-eyePointLocal);
            }
            return true;
        }
    };

    // Update texture matrix for cubemaps
    struct TexMatCallback : public osg::NodeCallback
    {
    public:

        TexMatCallback(osg::TexMat& tm) :
            _texMat(tm)
        {
        }

        virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
        {
            osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
            if (cv)
            {
                const osg::Matrix& MV = *(cv->getModelViewMatrix());
                const osg::Matrix R = osg::Matrix::rotate( osg::DegreesToRadians(112.0f), 0.0f,0.0f,1.0f)*
                                      osg::Matrix::rotate( osg::DegreesToRadians(90.0f), 1.0f,0.0f,0.0f);

                osg::Quat q = MV.getRotate();
                const osg::Matrix C = osg::Matrix::rotate( q.inverse() );

                _texMat.setMatrix( C*R );
            }

            traverse(node,nv);
        }

        osg::TexMat& _texMat;
    };

};

#endif // SKYBOX_H
