project("bytecode"
	LANGUAGES CXX)

add_library("bytecode" INTERFACE)
target_include_directories("bytecode"
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries("bytecode"
	INTERFACE "stream")