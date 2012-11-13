#include "Text3d.h"

Text3D::Text3D(osg::MatrixTransform *rootNode)
    :rootNode(rootNode), timer(0), frameCount(0)
{
    float radius = 1.0f;
    osg::Vec3 center(0.0f,0.0f,0.0f);
    float characterSize=radius*10.f;
    osg::Vec3 pos(center.x()-radius*.5f,center.y()-radius*.5f,center.z()-radius*.5f);
    text = new osgText::Text();
    osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform();
    osg::Geode* textGeode = new osg::Geode();

    pat->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    pat->addChild(textGeode);
    textGeode->addDrawable(text);
    text->setColor(osg::Vec4(0,0,1,1));
    text->setPosition(osg::Vec3d(0, 0, 0));
    text->setCharacterSize(characterSize);

    rootNode->addChild(pat);
    pat->setPosition(osg::Vec3(0, 0, -25));
}

std::ostringstream* Text3D::print()
{
    return &output;
}

void Text3D::update(double elapsed)
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
