project("compiler"
    LANGUAGES CXX)

file(GLOB_RECURSE COMPILER_SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("compiler" STATIC
    ${COMPILER_SOURCE_FILES})
target_include_directories("compiler"
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries("compiler"
    PUBLIC "bytecode"
    PUBLIC "tokenizer")