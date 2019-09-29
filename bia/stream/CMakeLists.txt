project("stream"
	LANGUAGES CXX)

add_library("stream")
target_include_directories("stream"
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries("stream"
	PUBLIC "gc")