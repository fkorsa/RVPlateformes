//#define VRJUGGLER

#ifdef VRJUGGLER

#include "OsgNav.h"

OsgNav::OsgNav(vrj::Kernel *kern, int &argc, char **argv) :
    Module(),
    vrj::OsgApp(kern),
    mSelectedMatrix(NULL),
    time_passed(0)
{

}

void OsgNav::latePreFrame()
{
    gmtl::Matrix44f world_transform;
    gmtl::invertFull( world_transform, mNavigator.getCurPos() );
    // Update the scene graph
    osg::Matrix osg_current_matrix;
    osg_current_matrix.set( world_transform.getData() );
    mNavTrans->setMatrix( osg_current_matrix );
}

void OsgNav::preFrame()
{
    vpr::Interval cur_time = mWand->getTimeStamp();
    vpr::Interval diff_time(cur_time - mLastPreFrameTime);
    if (mLastPreFrameTime.getBaseVal() >= cur_time.getBaseVal())
    {
        diff_time.secf(0.);
    }

    float time_delta = diff_time.secf();

    mLastPreFrameTime = cur_time;

    // Get wand data
    gmtl::Matrix44f wandMatrix = mWand->getData();

    if(moduleRegistry!=NULL)
    {
        if (mButton0->getData() == gadget::Digital::TOGGLE_ON)
        {
            moduleRegistry->getInputManager()->jump();
        }

        if (mButton1->getData() == gadget::Digital::TOGGLE_ON)
        {
            moduleRegistry->getInputManager()->moveLeft();
        }

        if (mButton2->getData() == gadget::Digital::TOGGLE_ON)
        {
            moduleRegistry->getInputManager()->moveRight();
        }
        moduleRegistry->getScene()->run(time_delta);
    }

    // Update the navigation using the time delta between
    mNavigator.update(time_delta);
}

void OsgNav::bufferPreDraw()
{
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClear( GL_COLOR_BUFFER_BIT );
}

void OsgNav::initScene()
{
    const std::string wand("VJWand");
    const std::string vjhead("VJHead");
    const std::string but0("VJButton0");
    const std::string but1("VJButton1");
    const std::string but2("VJButton2");
    const std::string but3("VJButton3");
    const std::string but4("VJButton4");
    const std::string but5("VJButton5");

    mWand.init(wand);
    mHead.init(vjhead);
    mButton0.init(but0);
    mButton1.init(but1);
    mButton2.init(but2);
    mButton3.init(but3);
    mButton4.init(but4);
    mButton5.init(but5);

    myInit();
}

void OsgNav::myInit()
{
    //The top level nodes of the tree
    mRootNode = new osg::Group();
    mNoNav    = new osg::Group();
    mNavTrans = new osg::MatrixTransform();

    mNavigator.init();

    mRootNode->addChild(mNoNav.get());
    mRootNode->addChild(mNavTrans.get());

    // run optimization over the scene graph
    osgUtil::Optimizer optimizer;
    optimizer.optimize(mRootNode.get());
}

#endif // VRJUGGLER
