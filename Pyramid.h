#ifndef PYRAMID_H
#define PYRAMID_H

#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/LightSource>
#include <osg/BoundingSphere>
#include <osgbCollision/CollisionShapes.h>
#include <osgbCollision/RefBulletObject.h>
#include <osgbDynamics/RigidBody.h>
#include <osg/MatrixTransform>
#include "Module.h"
#include "Constants.h"

/**
  Generates a pyramid of boxes and add it to the scene graph
**/
class Pyramid
{
public:
    Pyramid(ModuleRegistry* registry, int width, int depth, int size, float mass, osg::Vec3 center, osg::Texture2D *texture);

private:
    void addLayer(int width,int depth, int height);
    osg::MatrixTransform* createBox(const osg::Vec3& center);

    float mass;
    int size;
    ModuleRegistry* registry;
    osg::Group* rootNode;
    osg::Texture2D* texture;
    osg::Vec3 center;
};

#endif // PYRAMID_H
