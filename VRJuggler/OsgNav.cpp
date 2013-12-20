#define VRJUGGLER

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
  int i, j;  
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
    gmtl::Matrix44f headMatrix = mHead->getData();
    
    if(moduleRegistry!=NULL)
    {
        if(wandMatrix(1,1)!=0 && wandMatrix(3,3)!=0 && *(moduleRegistry->getAllowMovement()))
        {
            if (mButton0->getData() == gadget::Digital::TOGGLE_ON)
            {
                moduleRegistry->getInputManager()->jump();
            }
            float alpha = wandMatrix(2,1)/wandMatrix(1,1);
            float beta = wandMatrix(1,0);
            if(alpha > 0.6)
            {
                alpha = 0.6;
            }
            if(beta > 0.7)
            {
                beta = 0.7;
            }
            if(alpha < -0.6)
            {
                alpha = -0.6;
            }
            if(beta < -0.7)
            {
                beta = -0.7;
            }
            if(alpha > 0.1)
            {
                moduleRegistry->getInputManager()->moveBehind(0.8*alpha*alpha);
            }

            if(alpha < -0.2)
            {
                moduleRegistry->getInputManager()->moveFront(2*alpha*alpha);
            }
            
            if(beta > 0.1)
            {
                *(moduleRegistry->getCameraAngle()) -= beta*beta*time_delta*3;
            }

            if(beta < -0.1)
            {
                *(moduleRegistry->getCameraAngle()) += beta*beta*time_delta*3;
            }
//             if (mButton1->getData() == gadget::Digital::ON)
//             {
//                 *(moduleRegistry->getCameraAngle()) -= time_delta*2;
//             }
//             if (mButton2->getData() == gadget::Digital::ON)
//             {
//                 *(moduleRegistry->getCameraAngle()) += time_delta*2;
//             }
            
        }
        std::stringstream out;
        for(i = 0; i<4; i++)
        {
            for(j = 0; j<4; j++)
            {
                out << wandMatrix(i,j) << " ";
            }
            out << std::endl;
        }
        *(moduleRegistry->getText2D()->print()) = out.str();
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
    cameraMT = new osg::MatrixTransform(); 

    mNavigator.init();

    mRootNode->addChild(mNoNav.get());
    

    // run optimization over the scene graph
    osgUtil::Optimizer optimizer;
    optimizer.optimize(mRootNode.get());
    
    osg::notify( osg::ALWAYS ) << "my init" << std::endl;
   
    moduleRegistry->registerSceneView(getSceneView());
    moduleRegistry->registerRootNode(cameraMT.get());
    moduleRegistry->getScene()->createScene();
    
    osg::Matrix cameraMatrix;
    cameraMatrix.makeLookAt(osg::Vec3f(140, -400, 50), osg::Vec3f(140, 0, 50), osg::Vec3f(0, 0, 1));
    cameraMT->setMatrix(cameraMatrix);
    
    mNavTrans->addChild(cameraMT.get());
    mRootNode->addChild(mNavTrans.get());
    
    debugText = moduleRegistry->getText2D()->print();
}

#endif // VRJUGGLER
