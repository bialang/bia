cmake_minimum_required(VERSION 3.1)

# Project info
project(Bia)
set(Bia_VERSION_MAJOR 3)
set(Bia_VERSION_MINOR 60)
set(CMAKE_MODULE_PATH "${CMAKE_PROGRAM_PATH}/cmake_mod")

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
set(BIA_USE_OWN_UNICODE OFF CACHE BOOL "Whether to use own Unicode implementation instead of ICU. Not recommended.")
set(BIA_USE_STD_REGEX OFF CACHE BOOL "Whether to use std::regex instead of boost::regex. Not recommended.")
set(BIA_SHARED_BUILD ${BUILD_SHARED_LIBS})
set(BOOST_ROOT "" CACHE PATH "Boost library path.")
set(Boost_USE_STATIC_LIBS ON CACHE BOOL "Use static libs of boost.")

# Dependencies
find_path(MPIR_INCLUDE "mpir.h")
find_library(MPIR_LIB mpir)

set(BIA_INCLUDES ${MPIR_INCLUDE})
set(BIA_LIBRARIES ${MPIR_LIB})

# ICU
if(NOT BIA_USE_OWN_UNICODE)
  find_package(ICU REQUIRED COMPONENTS io i18n)
  
  list(APPEND BIA_INCLUDES ${ICU_INCLUDE_DIRS})
  list(APPEND BIA_LIBRARIES ${ICU_LIBRARIES})
endif(NOT BIA_USE_OWN_UNICODE)

# Boost.Regex
if(NOT BIA_USE_STD_REGEX)
  find_package(Boost REQUIRED COMPONENTS regex)

  list(APPEND BIA_INCLUDES ${Boost_INCLUDE_DIRS})
  list(APPEND BIA_LIBRARIES ${Boost_REGEX_LIBRARY})
endif(NOT BIA_USE_STD_REGEX)

if(BUILD_SHARED_LIBS)
  add_definitions(-DBIA_BUILDING)
endif(BUILD_SHARED_LIBS)

configure_file("${PROJECT_SOURCE_DIR}/Bia/config.in" "${PROJECT_SOURCE_DIR}/Bia/config.hpp")

include_directories(Bia)
add_subdirectory(Bia)

# Tests
option(BIA_BUILD_TESTS "Build tests" ON)

if(BIA_BUILD_TESTS)
  enable_testing()
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  
  add_subdirectory(tests)
endif(BIA_BUILD_TESTS)