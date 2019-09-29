project("stream"
	LANGUAGES CXX)

file(GLOB_RECURSE STREAM_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("stream" STATIC
	${STREAM_SOURCE_FILES})
target_include_directories("stream"
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries("stream"
	PUBLIC "gc")