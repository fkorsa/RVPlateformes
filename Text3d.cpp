#include "Text3d.h"

Text3D::Text3D(osg::MatrixTransform *rootNode)
    :rootNode(rootNode), timer(0), frameCount(0)
{
    float characterSize=10.f;
    text = new osgText::Text();
    osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform();
    osg::Geode* textGeode = new osg::Geode();

    pat->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    pat->addChild(textGeode);
    textGeode->addDrawable(text);
    text->setColor(osg::Vec4d(0,0,1,1));
    text->setPosition(osg::Vec3d(0, 0, 0));
    text->setCharacterSize(characterSize);

    rootNode->addChild(pat);
    pat->setPosition(osg::Vec3(0, 0, 0));
}

void Text3D::setText(std::string str)
{
    text->setText(str.c_str());
}

void Text3D::setColor(osg::Vec4d color)
{
    text->setColor(color);
}

void Text3D::setPosition(osg::Vec3d position)
{
    text->setPosition(position);
}