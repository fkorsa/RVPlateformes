#ifndef TEXT3D_H
#define TEXT3D_H

#include <osg/ShapeDrawable>
#include <osgUtil/SceneView>
#include <osg/Geode>
#include <osgText/Text>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/Transform>
#include <string>
#include <sstream>

class Text3D
{
public:
    Text3D(osg::MatrixTransform* rootNode);
    void update(double elapsed);
    std::ostringstream* print();

private:
    std::ostringstream output;
    osgText::Text* text;
    osg::Node* rootNode;
    double timer;
    int frameCount;
    std::string fps;
};

#endif // TEXT3D_H
