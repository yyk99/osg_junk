#
#
#

project (osg_junk)
cmake_minimum_required(VERSION 3.10)

option(BUILD_EXAMPLES "Build examples")

find_path(OSG_INCLUDE_DIR  osg 
	HINTS "C:/Program Files/OpenSceneGraph/include"
	HINTS "$ENV{LOCALAPPDATA}/OpenSceneGraph/include"
	)
if(NOT OSG_INCLUDE_DIR)
	message(FATAL_ERROR "OSG_INCLUDE_DIR not found")
endif()

find_path(OSG_LIB_DIR  osg.lib 
	HINTS "C:/Program Files/OpenSceneGraph/lib"
	HINTS "$ENV{LOCALAPPDATA}/OpenSceneGraph/lib"
	)
if(NOT OSG_LIB_DIR)
	message(FATAL_ERROR "OSG_LIB_DIR not found")
endif()

add_subdirectory(examples)

# end of file
