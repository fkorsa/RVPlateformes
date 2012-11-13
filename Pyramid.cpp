#include "Pyramid.h"

/**
  Generates a pyramid of boxes and add it to the scene graph
**/
Pyramid::Pyramid(ModuleRegistry *registry, int width, int depth, int size, float mass, osg::Vec3 center, osg::Texture2D *texture)
{
    this->center = center;
    this->mass = mass;
    this->registry = registry;
    this->texture = texture;
    this->size = size;
    this->rootNode = new osg::Group;
    addLayer(width,depth,0);
    registry->getRootNode()->addChild(rootNode);
}

osg::MatrixTransform* Pyramid::createBox(const osg::Vec3& center)
{

    osg::Box* box = new osg::Box(center, size, size, size);
    osg::ShapeDrawable* shape = new osg::ShapeDrawable(box);
    osg::StateSet* state = new osg::StateSet();
    osg::Geode* geode = new osg::Geode();
    shape->setColor(osg::Vec4(1., 1., 1., 1.));
    state->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
    geode->addDrawable(shape);
    geode->setStateSet(state);

    // We need a MatrixTransform to move the box around
    osg::MatrixTransform* root = new osg::MatrixTransform;
    root->addChild(geode);

    // We add the box to the simulation
    btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG(geode);
    osg::ref_ptr<osgbDynamics::CreationRecord> cr = new osgbDynamics::CreationRecord;
    cr->_sceneGraph = root;
    cr->_shapeType = BOX_SHAPE_PROXYTYPE;
    cr->_mass = mass;
    cr->_restitution = 1.f;
    cr->_friction = 1.f;
    btRigidBody* body = osgbDynamics::createRigidBody(cr.get(), cs);

    registry->getDynamicsWorld()->addRigidBody(body,COL_OTHERS,COL_FLOOR|COL_BALL|COL_OTHERS);
    rootNode->addChild(root);

    return root;
}

void Pyramid::addLayer(int width,int depth, int height) {
        osg::Vec3 pos = center + osg::Vec3(-(width*size+(width-1)*size/2)/2+size/2,-(depth*size+(depth-1)*size/2)/2+size/2,height*size+size/2);
    for (int i=0;i<width;i++) {
        for (int j=0;j<depth;j++) {
            createBox(osg::Vec3(pos.x()+i*(size+size/2),pos.y()+j*(size+size/2),pos.z()));
        }
    }
    if ( width == 1 && depth == 1 ) return;
    addLayer(width>1?width-1:1,depth>1?depth-1:1,++height);
}
