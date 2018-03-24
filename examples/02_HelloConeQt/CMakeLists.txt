#
#
#

find_package(Qt5Widgets)
find_package(Qt5OpenGL)


add_executable(02_HelloConeQt 02_HelloConeQt.cpp)
target_link_libraries(02_HelloConeQt 
    debug ${OSG_LIB_DIR}/osgd.lib 
    optimized ${OSG_LIB_DIR}/osg.lib 
    debug ${OSG_LIB_DIR}/osgViewerd.lib 
    optimized ${OSG_LIB_DIR}/osgViewer.lib 
    debug ${OSG_LIB_DIR}/osgDBd.lib
    optimized ${OSG_LIB_DIR}/osgDB.lib
    debug ${OSG_LIB_DIR}/osgWidgetd.lib
    optimized ${OSG_LIB_DIR}/osgWidget.lib 
    debug ${OSG_LIB_DIR}/osgQtd.lib
    optimized ${OSG_LIB_DIR}/osgQt.lib

    debug ${OSG_LIB_DIR}/osgGAd.lib
    optimized ${OSG_LIB_DIR}/osgGA.lib
    
    Qt5::Widgets
    Qt5::OpenGL
    )