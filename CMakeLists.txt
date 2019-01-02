cmake_minimum_required(VERSION 3.1)

# Project info
project(Bia)
set(Bia_VERSION_MAJOR 3)
set(Bia_VERSION_MINOR 60)

# Set C++14
if(CMAKE_VERSION VERSION_LESS "3.1")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
  endif()
else()
  set(CMAKE_CXX_STANDARD 14)
endif()

# Project
set(BIA_BUILD_SHARED ON CACHE BOOL "Build shared library")

# Dependencies
find_path(MPIR_INCLUDE "mpir/mpir.h")
find_library(MPIR_LIB mpir)
#install(FILES ${MPIR_INCLUDE} DESTINATION "include/Bia")

if(BIA_BUILD_SHARED)
  add_definitions(-DBIA_BUILDING)
endif(BIA_BUILD_SHARED)

configure_file("${PROJECT_SOURCE_DIR}/Bia/config_cmake.in" "${PROJECT_SOURCE_DIR}/Bia/config_cmake.hpp")

include_directories(${MPIR_INCLUDE})
include_directories(Bia)
add_subdirectory(Bia)

# Tests
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(BUILD_TESTS)