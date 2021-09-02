cmake_minimum_required(VERSION 3.1)

project(bia
	VERSION 0.0.0
	LANGUAGES CXX)

set(BIALANG_VERSION_MAJOR 0)
set(BIALANG_VERSION_MINOR 0)
set(BIALANG_VERSION "${BIALANG_VERSION_MAJOR}.${BIALANG_VERSION_MINOR}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Builds the Bia library as a shared library." ON)
option(BIA_BUILD_EXAMPLES "Builds the example programs." ON)
option(BIA_ENABLE_DEV_BACKTRACING "Enables C++ backtracing. Intended for development." OFF)
option(BIA_ENABLE_SANITIZER "Enables the use of sanitizers." OFF)
option(BIA_DEVELOPER "Enables developer mode." OFF)

if(BIA_ENABLE_SANITIZER)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address")
	set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -g -fsanitize=address")
endif()

# backtracing
if(BIA_ENABLE_DEV_BACKTRACING)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/backward-cpp")
endif()

if(BIA_DEVELOPER)
	option(BIA_DEVELOPER_DISASSEMBLY "Enables the disassembly output for the bytecode." ON)
endif()


# language
add_subdirectory("bia")


# testing
include(CTest)
if(BUILD_TESTING)
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
