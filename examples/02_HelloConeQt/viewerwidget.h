//
// Copyright (c) 2018
// Use of this source code is governed by a license that
// can be found in the LICENSE file.
//

#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>

#include <QWidget>
#include <QTimer>

namespace osgQt {
class GraphicsWindowQt;
}

class ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
    ViewerWidget(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::CompositeViewer::SingleThreaded);

    QWidget* addViewWidget(osgQt::GraphicsWindowQt *gw, osg::ref_ptr<osg::Node> scene);

    osgQt::GraphicsWindowQt *createGraphicsWindow(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);

    virtual void paintEvent(QPaintEvent* event);

public:

    static osg::Node *CreateConvexHull();

protected:

    QTimer _timer;
};

#endif
