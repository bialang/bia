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
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared library.")
set(PCRE2_STATIC ON CACHE BOOL "Whether the static PCRE2 library is used or not.")
set(BIA_SHARED_BUILD ${BUILD_SHARED_LIBS})

# Dependencies
find_path(MPIR_INCLUDE "mpir/mpir.h")
find_library(MPIR_LIB mpir)
find_package(Boost REQUIRED COMPONENTS regex)

if(BUILD_SHARED_LIBS)
  add_definitions(-DBIA_BUILDING)
endif(BUILD_SHARED_LIBS)

configure_file("${PROJECT_SOURCE_DIR}/Bia/config.in" "${PROJECT_SOURCE_DIR}/Bia/config.hpp")
configure_file("${PROJECT_SOURCE_DIR}/Bia/internal_config.in" "${PROJECT_SOURCE_DIR}/Bia/internal_config.hpp")

include_directories(${MPIR_INCLUDE})
include_directories(Bia)
add_subdirectory(Bia)

# Tests
option(BIA_BUILD_TESTS "Build tests" ON)

if(BIA_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(BIA_BUILD_TESTS)