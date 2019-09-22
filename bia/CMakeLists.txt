project("bia"
	LANGUAGES CXX)

set(BIA_VERSION_MAJOR 4)
set(BIA_VERSION_MINOR 0)

#add_subdirectory("external")
add_subdirectory("exception")
add_subdirectory("util")
add_subdirectory("gc")

file(GLOB BIA_HEADER_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/bia/*.hpp")

file(GLOB BIA_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

#add_library("bia" ${BIA_SOURCE_FILES})
#target_link_libraries("bia"
#		"util" "gc")