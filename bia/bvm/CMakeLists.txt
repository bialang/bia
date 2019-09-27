project("bvm"
    LANGUAGES CXX)

file(GLOB_RECURSE BVM_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR})

add_library("bvm" STATIC
    ${BVM_SOURCE_FILES})
target_include_directories("bvm"
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries("bvm"
    PUBLIC "gc"
    PUBLIC "external")

if(BUILD_TESTS)
    add_subdirectory("tests")
endif()