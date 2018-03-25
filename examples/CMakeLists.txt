#
#
#

include_directories(${OSG_INCLUDE_DIR})

set (example_directories
01_HelloCone
02_HelloConeQt
03_HelloBezier
)

foreach (d ${example_directories})
	add_subdirectory(${d})
endforeach(d)

# end of file