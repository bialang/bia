project("util"
		LANGUAGES CXX)

# Bulid library
file(GLOB_RECURSE UTIL_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("util" STATIC ${UTIL_SOURCE_FILES})
target_include_directories("util"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")

# Thread backend
set(BIA_THREAD_BACKEND "std::thread"
	CACHE STRING "The thread backend that should be used for creating threads in Bia and in its implementation.")
set_property(CACHE BIA_THREAD_BACKEND
	PROPERTY STRINGS "std::thread" "boost::thread")

if(${BIA_THREAD_BACKEND} STREQUAL "std::thread")
	set(BIA_THREAD_BACKEND_STD ON)

	find_package(Threads REQUIRED)
	target_link_libraries("util" ${CMAKE_THREAD_LIBS_INIT})
else()
	set(BIA_THREAD_BACKEND_BOOST ON)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/util/config.hpp")

# Tests
if(BIA_BUILD_TESTS)
	add_subdirectory("tests")
endif()
