cmake_minimum_required(VERSION 3.1)

project(bialang
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

option(BIA_BUILD_BIA_TOOL "Builds the command line tool for Bia." OFF)
option(BUILD_SHARED_LIBS "Builds the Bia library as a shared library." ON)
option(BIA_BUILD_TESTS "Builds the tests for the Bia library." ON)
option(BIA_BUILD_EXAMPLES "Builds the example programs." ON)
option(BIA_ENABLE_DEV_BACKTRACING "Enables C++ backtracing. Intended for development." OFF)
option(BIA_ENABLE_SANITIZER "Enables the use of sanitizers." OFF)

if(BIA_ENABLE_SANITIZER)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address")
	set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -g -fsanitize=address")
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release
		CACHE STRING "Build type." FORCE)
endif()

# backtracing
if(BIA_ENABLE_DEV_BACKTRACING)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/backward-cpp")
endif()


# language
add_subdirectory("bia")


# testing
if(BIA_BUILD_TESTS)
	include(CTest)
	set(CATCH_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Catch2")
	enable_testing()
	option(BIA_BUILD_BENCHMARKS "Build additional benchmark tests." OFF)
	add_subdirectory("tests")
endif()

# examples
if(BIA_BUILD_EXAMPLES)
	add_subdirectory("examples")
endif()


# CPack
set(CPACK_PACKAGE_NAME "Bia")
set(CPACK_PACKAGE_DESCRIPTION "Embedded scripting language")
set(CPACK_PACKAGE_VENDOR "Bialang")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Bia/${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

include(CPack)
