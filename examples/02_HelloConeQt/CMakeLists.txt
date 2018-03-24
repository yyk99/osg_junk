#
#
#

find_package(Qt5Widgets)
find_package(Qt5OpenGL)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (TARGET_UI_SRC
    mainwindow.ui
)

set (TARGET_SRC 
    02_HelloConeQt.cpp
    mainwindow.cpp
    mainwindow.h
)

qt5_wrap_cpp(TARGET_MOC_FILES ${TARGET_SRC})
qt5_wrap_ui(TARGET_UI_H ${TARGET_UI_SRC})

add_executable(02_HelloConeQt ${TARGET_SRC} ${TARGET_MOC_FILES} ${TARGET_UI_H})
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