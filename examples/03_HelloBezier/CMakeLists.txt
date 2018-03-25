#
#
#

add_executable(03_HelloBezier 03_HelloBezier.cpp terrain_coords.h)
target_link_libraries(03_HelloBezier 
    debug ${OSG_LIB_DIR}/osgd.lib 
    optimized ${OSG_LIB_DIR}/osg.lib 
    debug ${OSG_LIB_DIR}/osgViewerd.lib 
    optimized ${OSG_LIB_DIR}/osgViewer.lib 
    debug ${OSG_LIB_DIR}/osgDBd.lib 
    optimized ${OSG_LIB_DIR}/osgDB.lib 
    
    )