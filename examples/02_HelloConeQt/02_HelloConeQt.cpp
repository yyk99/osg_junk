//
// yyk 2018
//

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Texture2D>
#include <osgUtil/ShaderGen>

#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/MultiTouchTrackballManipulator>

#include <osgQt/GraphicsWindowQt>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osg/Math>

#include <QWidget>
#include <QTimer>
#include <QGridLayout>
#include <QApplication>

osg::Node *CreateConvexHull()
{
    osg::ConvexHull* mesh = new osg::ConvexHull;
    osg::Vec3Array* vertices = new osg::Vec3Array(4);
    (*vertices)[0].set(9.0 + 0.0f, -1.0f + 2.0f, -1.0f + 0.0f);
    (*vertices)[1].set(9.0 + 1.0f, -1.0f + 0.0f, -1.0f + 0.0f);
    (*vertices)[2].set(9.0 + 2.0f, -1.0f + 2.0f, -1.0f + 0.0f);
    (*vertices)[3].set(9.0 + 1.0f, -1.0f + 1.0f, -1.0f + 2.0f);
    osg::UByteArray* indices = new osg::UByteArray(12);
    (*indices)[0] = 0;
    (*indices)[1] = 2;
    (*indices)[2] = 1;
    (*indices)[3] = 0;
    (*indices)[4] = 1;
    (*indices)[5] = 3;
    (*indices)[6] = 1;
    (*indices)[7] = 2;
    (*indices)[8] = 3;
    (*indices)[9] = 2;
    (*indices)[10] = 0;
    (*indices)[11] = 3;
    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    
    return new osg::ShapeDrawable(mesh);
}

class ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
    ViewerWidget(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::CompositeViewer::SingleThreaded) : QWidget(parent, f)
    {
        setThreadingModel(threadingModel);

        // disable the default setting of viewer.done() by pressing Escape.
        setKeyEventSetsDone(0);

        float radius = 0.8f;
        float height = 1.5f;
        osg::TessellationHints* hints = new osg::TessellationHints;
        hints->setDetailRatio(0.5f);

        auto sphere = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints);
        sphere->setColor(osg::Vec4(207./256, 181./256, 59./256, 1.0f));

        auto box = new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f), 2 * radius), hints);

        auto cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f), radius, height), hints);
        cylinder->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));

        auto capsule = new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height), hints);

        QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), sphere);
        QWidget* widget2 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), box);
        QWidget* widget3 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), cylinder);
        QWidget* widget4 = addViewWidget(createGraphicsWindow(0, 0, 100, 100), CreateConvexHull());

        auto cone = new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints);
        cone->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));

        QWidget* popupWidget = addViewWidget(createGraphicsWindow(900, 100, 320, 240, "Popup window", true), cone);
        popupWidget->show();

        QGridLayout* grid = new QGridLayout;
        grid->addWidget(widget1, 0, 0);
        grid->addWidget(widget2, 0, 1);
        grid->addWidget(widget3, 1, 0);
        grid->addWidget(widget4, 1, 1);
        setLayout(grid);

        connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
        _timer.start(10);
    }

    QWidget* addViewWidget(osgQt::GraphicsWindowQt* gw, osg::ref_ptr<osg::Node> scene)
    {
        osgViewer::View* view = new osgViewer::View;
        addView(view);

        osg::Camera* camera = view->getCamera();
        camera->setGraphicsContext(gw);

        const osg::GraphicsContext::Traits* traits = gw->getTraits();

        camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
        camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
        camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 10000.0f);

        view->setSceneData(scene);
        view->addEventHandler(new osgViewer::StatsHandler);
        view->setCameraManipulator(new osgGA::MultiTouchTrackballManipulator);
        gw->setTouchEventsEnabled(true);
        return gw->getGLWidget();
    }

    osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false)
    {
        osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
        traits->windowName = name;
        traits->windowDecoration = windowDecoration;
        traits->x = x;
        traits->y = y;
        traits->width = w;
        traits->height = h;
        traits->doubleBuffer = true;
        traits->alpha = ds->getMinimumNumAlphaBits();
        traits->stencil = ds->getMinimumNumStencilBits();
        traits->sampleBuffers = ds->getMultiSamples();
        traits->samples = ds->getNumMultiSamples();

        return new osgQt::GraphicsWindowQt(traits.get());
    }

    virtual void paintEvent(QPaintEvent* event)
    {
        frame();
    }

protected:

    QTimer _timer;
};


//osg::Geode* createShapes()
//{
//    osg::Geode* geode = new osg::Geode();
//
//    // ---------------------------------------
//    // Set up a StateSet to texture the objects
//    // ---------------------------------------
//    osg::StateSet* stateset = new osg::StateSet();
//
//    stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);
//
//    geode->setStateSet(stateset);
//
//    float radius = 0.8f;
//    float height = 1.5f;
//
//    osg::TessellationHints* hints = new osg::TessellationHints;
//    hints->setDetailRatio(0.5f);
//
//    auto shape = new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints);
//    shape->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//    geode->addDrawable(shape);
//
//    return geode;
//}

#include "mainwindow.h"

int main(int argc, char** argv)
{
    osg::ArgumentParser arguments(&argc, argv);

#if QT_VERSION >= 0x050000
    // Qt5 is currently crashing and reporting "Cannot make QOpenGLContext current in a different thread" when the viewer is run multi-threaded, this is regression from Qt4
    osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::ViewerBase::SingleThreaded;
#else
    osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::ViewerBase::CullDrawThreadPerContext;
#endif

    while (arguments.read("--SingleThreaded")) threadingModel = osgViewer::ViewerBase::SingleThreaded;
    while (arguments.read("--CullDrawThreadPerContext")) threadingModel = osgViewer::ViewerBase::CullDrawThreadPerContext;
    while (arguments.read("--DrawThreadPerContext")) threadingModel = osgViewer::ViewerBase::DrawThreadPerContext;
    while (arguments.read("--CullThreadPerCameraDrawThreadPerContext")) threadingModel = osgViewer::ViewerBase::CullThreadPerCameraDrawThreadPerContext;

#if QT_VERSION >= 0x040800
    // Required for multi threaded QGLWidget on Linux/X11, see http://blog.qt.io/blog/2011/06/03/threaded-opengl-in-4-8/
    if (threadingModel != osgViewer::ViewerBase::SingleThreaded)
        QApplication::setAttribute(Qt::AA_X11InitThreads);
#endif

    QApplication app(argc, argv);

    auto mainWindow = new MainWindow();
#if 1
    ViewerWidget* viewWidget = new ViewerWidget(mainWindow->centralWidget(), Qt::Widget, threadingModel);
    mainWindow->addViewer(viewWidget);
#else
    //auto widget = new QWidget(mainWindow->centralWidget());
    //widget->setStyleSheet("background-color:green;");
#endif
    
    mainWindow->show();

    return app.exec();
}
