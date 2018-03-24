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

osg::Geode* createShapes()
{
    osg::Geode* geode = new osg::Geode();

    // ---------------------------------------
    // Set up a StateSet to texture the objects
    // ---------------------------------------
    osg::StateSet* stateset = new osg::StateSet();

    stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    geode->setStateSet(stateset);

    float radius = 0.8f;
    float height = 1.5f;

    osg::TessellationHints* hints = new osg::TessellationHints;
    hints->setDetailRatio(0.5f);

    auto shape = new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints);
    shape->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    geode->addDrawable(shape);

    return geode;
}

int main(int, char **)
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    // add model to viewer.
    viewer.setSceneData(createShapes());

    return viewer.run();
}
