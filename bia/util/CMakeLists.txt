project("util"
		LANGUAGES CXX)

# Bulid library
file(GLOB_RECURSE UTIL_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("util" STATIC
	${UTIL_SOURCE_FILES})
target_include_directories("util"
	PUBLIC ${BIA_BIA_CONFIG_PATH}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

create_tests("util")
