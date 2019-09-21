project("exception"
	LANGUAGE CXX)

add_library("exception")

target_include_directories("exception"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")