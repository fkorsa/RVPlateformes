#include "Text2d.h"

Text2D::Text2D(osg::MatrixTransform *rootNode)
    :rootNode(rootNode), timer(0), frameCount(0)
{

    text = new osgText::Text();
    osg::MatrixTransform* matrixTransform = new osg::MatrixTransform();
    osg::Projection* projectionMatrix = new osg::Projection();
    osg::Geode* textGeode = new osg::Geode();

    matrixTransform->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    matrixTransform->addChild(projectionMatrix);
    projectionMatrix->setMatrix(osg::Matrix::ortho2D(0,1280,0,1024));
    projectionMatrix->addChild(textGeode);
    textGeode->addDrawable(text);
    text->setColor(osg::Vec4(0,0,0,1));
    text->setPosition(osg::Vec3d(0, 0, 0));

    rootNode->addChild(matrixTransform);

}

std::ostringstream* Text2D::print()
{
    return &output;
}

void Text2D::update(double elapsed)
{
    timer += elapsed;
    frameCount++;
    if (timer>1.)
    {
        std::ostringstream ss; ss <<frameCount;
        fps = "FPS: " + ss.str();
        frameCount = 0;
        timer = 0;
    }
    text->setText((fps+"\n"+output.str()).c_str());
    output.flush();
}
