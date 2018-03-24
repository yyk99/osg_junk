#
#
#

add_executable(01_HelloCone 01_HelloCone.cpp)
target_link_libraries(01_HelloCone 
    debug ${OSG_LIB_DIR}/osgd.lib 
    optimized ${OSG_LIB_DIR}/osg.lib 
    debug ${OSG_LIB_DIR}/osgViewerd.lib 
    optimized ${OSG_LIB_DIR}/osgViewer.lib 
    debug ${OSG_LIB_DIR}/osgDBd.lib 
    optimized ${OSG_LIB_DIR}/osgDB.lib 
    
    )