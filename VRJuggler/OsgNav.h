#ifndef OSGNAV_H
#define OSGNAV_H

#include "Module.h"

#ifdef VRJUGGLER

#include <vrj/vrjConfig.h>

#include <iostream>
#include <iomanip>
#include <math.h>

#include <vrj/Draw/OGL/GlApp.h>

#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>

//OSG  includes
#include <osg/Matrix>
#include <osg/Transform>
#include <osg/MatrixTransform>

#include <osgUtil/SceneView>

#include <vrj/Draw/OSG/OsgApp.h>

#include <osg/Math>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Vec3>
#include <osgUtil/Optimizer>
#include <osgDB/ReadFile>

#include <gmtl/Vec.h>
#include <gmtl/Coord.h>
#include <gmtl/Xforms.h>
#include <gmtl/Math.h>

class OsgNav : public vrj::OsgApp, public Module
{
public:
    OsgNav(vrj::Kernel* kern, int& argc, char** argv);

    virtual ~OsgNav()
    {}

    virtual void initScene();

    void myInit();

    void initTweek(int& argc, char* argv[]);

    virtual osg::Group* getScene()
    {
        return mRootNode.get();
    }

    virtual void configSceneView(osgUtil::SceneView* newSceneViewer)
    {
        vrj::OsgApp::configSceneView(newSceneViewer);

        sceneView = newSceneViewer;
        /*newSceneViewer->getLight()->setAmbient(osg::Vec4(0.3f,0.3f,0.3f,1.0f));
        newSceneViewer->getLight()->setDiffuse(osg::Vec4(0.9f,0.9f,0.9f,1.0f));
        newSceneViewer->getLight()->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f));*/
    }

    osgUtil::SceneView* getSceneView()
    {
        return sceneView;
    }

    osg::ref_ptr<osg::Node> getRootNode()
    {
        return mNavTrans;
    }

    void bufferPreDraw();

    virtual void preFrame();

    virtual void latePreFrame();

    virtual void intraFrame()
    {}

    virtual void postFrame()
    {}

private:
    osg::ref_ptr<osg::Group>           mRootNode;
    osg::ref_ptr<osg::Group>           mNoNav;
    osg::ref_ptr<osg::MatrixTransform> mNavTrans;
    osg::ref_ptr<osg::MatrixTransform> mLanderTrans;
    osg::ref_ptr<osg::Node>            mModelLander;
    osg::ref_ptr<osg::MatrixTransform> mRotationLander[5];
    osg::Matrix 					   rotationMatrix[5];
    osg::Matrix 					   transMatrix[5];
    osg::ref_ptr<osg::MatrixTransform> mLandersTransArray[5];
    osg::MatrixTransform              *mSelectedMatrix;
    osg::SceneView                    *sceneView;
    OsgNavigator mNavigator;
    float time_passed;

    vpr::Interval mLastPreFrameTime;

public:
    gadget::PositionInterface  mWand;
    gadget::PositionInterface  mHead;
    gadget::DigitalInterface   mButton0;
    gadget::DigitalInterface   mButton1;
    gadget::DigitalInterface   mButton2;
    gadget::DigitalInterface   mButton3;
    gadget::DigitalInterface   mButton4;
    gadget::DigitalInterface   mButton5;
};

#endif // VRJUGGLER
#endif // OSGNAV_H
