project("tokenizer"
	LANGUAGES CXX)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/config.hpp")
	
create_library(STATIC
	PUBLIC "stream"
	PUBLIC "string")

add_executable("main" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries("main" "tokenizer")