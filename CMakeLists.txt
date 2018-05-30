#cmake_minimum_required(VERSION 3.1)

# Project info
project(Bia)
set(Bia_VERSION_MAJOR 3)
set(Bia_VERSION_MINOR 60)

# Set C++11
if(CMAKE_VERSION VERSION_LESS "3.1")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  endif()
else()
  set(CMAKE_CXX_STANDARD 11)
endif()

# Project
include_directories(Bia)

add_subdirectory(Bia)

# Tests
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(BUILD_TESTS)