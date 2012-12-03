#ifndef PYRAMID_H
#define PYRAMID_H

#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/LightSource>
#include <osg/BoundingSphere>
#include <osg/MatrixTransform>
#include "../Abstract/Module.h"
#include "../Abstract/MyMotionState.h"
#include "../Constants.h"

/**
  Generates a pyramid of boxes and add it to the scene graph
**/
class Pyramid
{
public:
    Pyramid(ModuleRegistry* registry, int width, int depth, int size, float mass, osg::Vec3 center, osg::Texture2D *texture);
    ~Pyramid();
    void reset();
private:
    void addLayer(int width,int depth, int height);
    void moveLayer(int width,int depth, int height);
    void createBox(const osg::Vec3& center);

    float mass;
    int size;
    ModuleRegistry* registry;
    osg::Group* rootNode;
    osg::Texture2D* texture;
    osg::Vec3 center;
    btRigidBody *bodiesList[1000];
    osg::ref_ptr<osg::MatrixTransform> mtList[1000];
    int numBodies;
};

#endif // PYRAMID_H
