project("util"
		LANGUAGES CXX)

# Thread backend
set(BIA_THREAD_BACKEND "std::thread"
	CACHE STRING "The thread backend that should be used for creating threads in Bia and in its implementation.")
set_property(CACHE BIA_THREAD_BACKEND
	PROPERTY STRINGS "std::thread" "boost::thread")

if(${BIA_THREAD_BACKEND} STREQUAL "std::thread")

else()

endif()

# Bulid library
file(GLOB_RECURSE UTIL_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("util" STATIC ${UTIL_SOURCE_FILES})
target_include_directories("util" PUBLIC "util/")

# Tests
if(BIA_BUILD_TESTS)
	add_subdirectory("tests")
endif()
