find_package(Catch2 2 QUIET)
if(NOT Catch2_FOUND)
  message(STATUS "Fetching Catch2")
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.7
  )
  FetchContent_GetProperties(Catch2)
  if(NOT Catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory("${Catch2_SOURCE_DIR}" "${Catch2_BINARY_DIR}")
  endif()
  list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
endif()

file(GLOB dirs "${CMAKE_CURRENT_SOURCE_DIR}/*")
include(Catch)
foreach(dir ${dirs})
  if(IS_DIRECTORY "${dir}")
    get_filename_component(name "${dir}" NAME)

    file(GLOB_RECURSE sources "${dir}/*.[ch]pp")
    add_executable(${name}_test ${sources})
    target_link_libraries(${name}_test PRIVATE bia::bia Catch2::Catch2)
    catch_discover_tests(${name}_test)
  endif()
endforeach()

set_property(TARGET bia_test PROPERTY CXX_STANDARD 17)
