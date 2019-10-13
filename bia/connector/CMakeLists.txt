project("connector"
	LANGUAGES CXX)

add_library("connector")
target_include_directories("connector"
	${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries("connector"
	PUBLIC "stack"
	PUBLIC "member_interface")
