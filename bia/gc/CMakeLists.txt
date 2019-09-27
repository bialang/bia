project("gc"
	LANGUAGES CXX)

file(GLOB_RECURSE GC_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("gc" STATIC
	${GC_SOURCE_FILES})
target_include_directories("gc"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
target_link_libraries("gc"
	PUBLIC "util"
	PUBLIC "exception")

# Tests
if(BIA_BUILD_TESTS)
	add_subdirectory("tests")
endif()
