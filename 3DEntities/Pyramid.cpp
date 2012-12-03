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
    numBodies = 0;
    addLayer(width,depth,0);
    registry->getRootNode()->addChild(rootNode);
}

void Pyramid::createBox(const osg::Vec3& center)
{
    osg::Box* box = new osg::Box(osg::Vec3f(), size, size, size);
    osg::ShapeDrawable* shape = new osg::ShapeDrawable(box);
    osg::StateSet* state = new osg::StateSet();
    osg::Geode* geode = new osg::Geode();
    shape->setColor(osg::Vec4(1., 1., 1., 1.));
    state->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
    geode->addDrawable(shape);
    geode->setStateSet(state);

    mtList[numBodies] = new osg::MatrixTransform;
    mtList[numBodies]->addChild(geode);
    osg::Matrix m;
    m.makeTranslate(center);
    mtList[numBodies]->setMatrix( m );

    MyMotionState* boxMotionState = new MyMotionState(mtList[numBodies]);

    btVector3 inertia(0, 0, 0);
    btCompoundShape* cs = new btCompoundShape;
    btBoxShape* boxShape = new btBoxShape(btVector3(size, size, size)*0.5);
    btTransform trans;
    trans.setIdentity();
    cs->addChildShape(trans, boxShape);
    btRigidBody::btRigidBodyConstructionInfo rb(mass, boxMotionState, cs, inertia);

    btRigidBody* body = new btRigidBody(rb);
    bodiesList[numBodies] = body;
    body->setRestitution(0.3f);
    body->setFriction(.1);

    registry->getDynamicsWorld()->addRigidBody(body,COL_OTHERS,COL_FLOOR|COL_BALL|COL_OTHERS);
    rootNode->addChild(mtList[numBodies++].get());
}

void Pyramid::addLayer(int width,int depth, int height)
{
    osg::Vec3 pos = center + osg::Vec3(-(width*size+(width-1)*size/2)/2+size/2,
                                       -(depth*size+(depth-1)*size/2)/2+size/2,
                                       height*size+size/2);
    for (int i=0;i<width;i++)
    {
        for (int j=0;j<depth;j++)
        {
            createBox(osg::Vec3(pos.x()+i*(size+size/2),pos.y()+j*(size+size/2),pos.z()));
        }
    }
    if ( width == 1 && depth == 1 ) return;
    addLayer(width>1?width-1:1,depth>1?depth-1:1,++height);
}

Pyramid::~Pyramid()
{
  for(int i = 0; i<numBodies; i++)
  {
      registry->getDynamicsWorld()->removeRigidBody(bodiesList[i]);
      delete bodiesList[i]->getMotionState();
      delete bodiesList[i];
      rootNode->removeChild(mtList[i].get());
  }
}