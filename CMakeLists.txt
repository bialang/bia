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

# Dependencies
find_path(MPIR_INCLUDE "mpir/mpir.h")
find_library(MPIR_LIB mpir)
#install(FILES ${MPIR_INCLUDE} DESTINATION "include/Bia")

if(BUILD_SHARED_LIBS)
  add_definitions(-DBIA_BUILDING)
endif(BUILD_SHARED_LIBS)

# Implementation hiding
option(BIA_HIDE_MPIR_IMPL "Hide the MPIR include headers." ON)
option(BIA_HIDE_BOOST_REGEX_IMPL "Hide the Boost.Regex headers." ON)

include(CheckTypeSize)
set(CMAKE_REQUIRED_INCLUDES ${MPIR_INCLUDE})
set(CMAKE_REQUIRED_LIBRARIES ${MPIR_LIB})
set(CMAKE_EXTRA_INCLUDE_FILES "mpir/mpir.h")

function(set_hidden_size NAME TYPE)
  if(BIA_HIDE_${NAME}_IMPL)
    set(CMAKE_REQUIRED_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
    unset(HAVE_BIA_${NAME}_IMPL_SIZE_DEBUG CACHE)
    check_type_size(${TYPE} BIA_${NAME}_IMPL_SIZE_DEBUG)

    set(CMAKE_REQUIRED_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
    unset(HAVE_BIA_${NAME}_IMPL_SIZE_RELEASE CACHE)
    check_type_size(${TYPE} BIA_${NAME}_IMPL_SIZE_RELEASE)

    message(STATUS ${TYPE} " is " ${BIA_${NAME}_IMPL_SIZE_DEBUG} "|" ${BIA_${NAME}_IMPL_SIZE_RELEASE} " bytes big")
  else(BIA_HIDE_${NAME}_IMPL)
    set(BIA_${NAME}_IMPL_SIZE_DEBUG "sizeof(mpz_t)")
    set(BIA_${NAME}_IMPL_SIZE_RELEASE "sizeof(mpz_t)")
  endif(BIA_HIDE_${NAME}_IMPL)
endfunction()

set_hidden_size(MPIR "mpz_t")
set_hidden_size(BOOST_REGEX "boost::regex")

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