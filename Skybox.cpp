#include "Skybox.h"

Skybox::Skybox(osg::MatrixTransform* rootNode,const std::string directory)
{
    this->directory = directory;
    rootNode->addChild(createSkyBox());
}

osg::TextureCubeMap* Skybox::readCubeMap()
{

    std::string base = "data/textures/" + directory + "/";

    osg::TextureCubeMap* cubemap = new osg::TextureCubeMap;

    osg::Image* imagePosX = osgDB::readImageFile(base+"left.jpg");
    osg::Image* imageNegX = osgDB::readImageFile(base+"right.jpg");
    osg::Image* imagePosY = osgDB::readImageFile(base+"back.jpg");
    osg::Image* imageNegY = osgDB::readImageFile(base+"front.jpg");
    osg::Image* imagePosZ = osgDB::readImageFile(base+"top.jpg");
    osg::Image* imageNegZ = osgDB::readImageFile(base+"bottom.jpg");

    if (imagePosX && imageNegX && imagePosY && imageNegY && imagePosZ && imageNegZ)
    {
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, imageNegY);
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, imagePosY);
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, imageNegZ);
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, imagePosZ);
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, imageNegX);
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, imagePosX);

        cubemap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        cubemap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
        cubemap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

        cubemap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
        cubemap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    }

    return cubemap;
}

osg::Node* Skybox::createSkyBox()
{

    osg::StateSet* stateset = new osg::StateSet();

    osg::TexEnv* te = new osg::TexEnv;
    te->setMode(osg::TexEnv::REPLACE);
    stateset->setTextureAttributeAndModes(0, te, osg::StateAttribute::ON);

    osg::TexGen *tg = new osg::TexGen;
    tg->setMode(osg::TexGen::NORMAL_MAP);
    stateset->setTextureAttributeAndModes(0, tg, osg::StateAttribute::ON);

    osg::TexMat *tm = new osg::TexMat;
    stateset->setTextureAttribute(0, tm);

    osg::TextureCubeMap* skymap = readCubeMap();
    stateset->setTextureAttributeAndModes(0, skymap, osg::StateAttribute::ON);

    stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    stateset->setMode( GL_CULL_FACE, osg::StateAttribute::OFF );

    // clear the depth to the far plane.
    osg::Depth* depth = new osg::Depth;
    depth->setFunction(osg::Depth::ALWAYS);
    depth->setRange(1.0,1.0);
    stateset->setAttributeAndModes(depth, osg::StateAttribute::ON );

    stateset->setRenderBinDetails(-1,"RenderBin");

    osg::Drawable* drawable = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),1));

    osg::Geode* geode = new osg::Geode;
    geode->setCullingActive(false);
    geode->setStateSet( stateset );
    geode->addDrawable(drawable);


    osg::Transform* transform = new MoveEarthySkyWithEyePointTransform;
    transform->setCullingActive(false);
    transform->addChild(geode);

    osg::ClearNode* clearNode = new osg::ClearNode;
//  clearNode->setRequiresClear(false);
    clearNode->setCullCallback(new TexMatCallback(*tm));
    clearNode->addChild(transform);

    return clearNode;
}
