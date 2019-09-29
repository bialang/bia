project("bia"
	LANGUAGES CXX)

set(BIA_VERSION_MAJOR 4)
set(BIA_VERSION_MINOR 0)

include(TestBigEndian)
test_big_endian(BIA_BIG_ENDIAN)

if(NOT BIA_BIG_ENDIAN)
	set(BIA_LITTLE_ENDIAN ON)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/bia/config.hpp")

set(BIA_BIA_CONFIG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bia/config.hpp")

add_subdirectory("exception")
add_subdirectory("util")
add_subdirectory("thread")
add_subdirectory("gc")
add_subdirectory("stream")
add_subdirectory("string")
add_subdirectory("bvm")