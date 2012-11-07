#include "Scene.h"

Scene::Scene()
{
    rootNode = new osg::Group;
}

void Scene::createScene()
{
    // How to add a model to the scene
    // LOL
    osg::Node *  model = osgDB::readNodeFile("data/starthing.obj");
    osg::PositionAttitudeTransform * modelPAT = new osg::PositionAttitudeTransform();
    modelPAT->setPosition(osg::Vec3d(0, 0, -20));
    modelPAT->addChild(model);
    rootNode->addChild(modelPAT);

    moduleRegistry->getSceneView()->setSceneData(rootNode);
}
