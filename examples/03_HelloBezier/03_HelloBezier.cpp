//
// yyk 2018
//

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Texture2D>
#include <osgUtil/ShaderGen>

#include <osgViewer/Viewer>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osg/Math>

// for the grid data..
#include "terrain_coords.h"

osg::Geode* createTerrain()
{
    osg::Geode* geode = new osg::Geode();


    // ---------------------------------------
    // Set up a StateSet to texture the objects
    // ---------------------------------------
    osg::StateSet* stateset = new osg::StateSet();

    osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile("Images/lz.rgb");
    if (image)
    {
        osg::Texture2D* texture = new osg::Texture2D;
        texture->setImage(image);
        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
        stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
    }

    stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    geode->setStateSet(stateset);

#if 0
    float radius = 0.8f;
    float height = 1.0f;

    osg::TessellationHints* hints = new osg::TessellationHints;
    hints->setDetailRatio(0.5f);

    geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f), 2 * radius), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f), radius, height), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height), hints));
#endif

    osg::HeightField* grid = new osg::HeightField;
    grid->allocate(38, 39);
    grid->setXInterval(0.28f);
    grid->setYInterval(0.28f);

    for (unsigned int r = 0; r < 39; ++r)
    {
        for (unsigned int c = 0; c < 38; ++c)
        {
            grid->setHeight(c, r, vertex[r + c * 39][2]);
        }
    }
    geode->addDrawable(new osg::ShapeDrawable(grid));

    return geode;
}

int main(int, char **)
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    // add model to viewer.
    viewer.setSceneData(createTerrain());

    return viewer.run();
}
