find_package(Catch2 2 QUIET)
if(NOT Catch2_FOUND)
  message(STATUS "Fetching Catch2 from github.com")
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    URL https://github.com/catchorg/Catch2/archive/refs/tags/v2.13.8.zip
    URL_HASH SHA256=de0fd1f4c51a1021ffcb33a4d42028545bf1a0665a4ab59ddb839a0cc93f03a5
  )
  FetchContent_GetProperties(Catch2)
  if(NOT catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory("${catch2_SOURCE_DIR}" "${catch2_BINARY_DIR}")
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
