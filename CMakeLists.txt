cmake_minimum_required(VERSION 3.11)

project(
  bia
  VERSION 0.0.0
  DESCRIPTION "Easily embedded C++ scripting language."
  LANGUAGES CXX
)

set(BIALANG_VERSION_MAJOR 0)
set(BIALANG_VERSION_MINOR 0)
set(BIALANG_VERSION "${BIALANG_VERSION_MAJOR}.${BIALANG_VERSION_MINOR}")

set(default_build_type Debug)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type for ${PROJECT_NAME} to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE
      "${default_build_type}"
      CACHE STRING "Build type." FORCE
  )
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Builds the Bia library as a shared library." ON)
option(BIA_BUILD_EXAMPLES "Builds the example programs." OFF)
option(BIA_ENABLE_DEV_BACKTRACING "Enables C++ backtracing. Intended for development." OFF)
option(BIA_ENABLE_SANITIZER "Enables the use of sanitizers." OFF)
option(BIA_DEVELOPER "Enables developer mode." OFF)
option(BIA_DEVELOPER_DISASSEMBLY "Enables the disassembly output for the bytecode." ON)

if(BIA_ENABLE_SANITIZER)
  set(CMAKE_CXX_FLAGS_DEBUG
      "${CMAKE_CXX_FLAGS_DEBUG} -g -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address"
  )
  set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -g -fsanitize=address")
endif()

# backtracing
if(BIA_ENABLE_DEV_BACKTRACING)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/backward-cpp")
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

add_subdirectory(bia)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

# examples
if(BIA_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# Installing
include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${PROJECT_NAME}-config.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION "${LIBRARY_INSTALL_DIR}/cmake/${PROJECT_NAME}"
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME}
)
install(
  EXPORT ${PROJECT_NAME}-targets
  DESTINATION lib/cmake/${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  EXPORT_LINK_INTERFACE_LIBRARIES
)
install(
  DIRECTORY bia
  DESTINATION include/${PROJECT_NAME}
  FILES_MATCHING
  REGEX "\\.(hpp|h)$"
)

# CPack
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "Yunus Ayar <greybley@yahoo.de>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_DESCRIPTION "Some detailed description.")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR DEB TGZ)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
