project("tokenizer"
	LANGUAGES CXX)

file(GLOB_RECURSE TOKENIZER_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("tokenizer" STATIC
	${TOKENIZER_SOURCE_FILES})
target_include_directories("tokenizer"
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries("tokenizer"
	PUBLIC "stream"
	PUBLIC "string")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/config.hpp")

create_tests("tokenizer")