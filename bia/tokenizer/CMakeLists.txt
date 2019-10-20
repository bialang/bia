project("tokenizer"
	LANGUAGES CXX)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/config.hpp")
	
create_library(STATIC
	PUBLIC "stream"
	PUBLIC "string")