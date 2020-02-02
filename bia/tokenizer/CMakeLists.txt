project(tokenizer
	LANGUAGES CXX)
	
create_library(STATIC
	PUBLIC string)

add_executable(main "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(main tokenizer)