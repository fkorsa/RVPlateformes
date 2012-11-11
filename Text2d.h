#ifndef TEXT2D_H
#define TEXT2D_H

#include <osg/ShapeDrawable>
#include <osgUtil/SceneView>
#include <osg/Geode>
#include <osgText/Text>
#include <osg/Projection>
#include <osg/MatrixTransform>
#include <osg/Transform>
#include <string>
#include <sstream>

class Text2D
{
public:
    Text2D(osg::Group* rootNode);

    void update(double elapsed);
    std::ostringstream* print();

private:
    std::ostringstream output;
    osgText::Text* text;
    osg::Group* rootNode;
    double timer;
    int frameCount;
    std::string fps;

};

#endif // TEXT2D_H
