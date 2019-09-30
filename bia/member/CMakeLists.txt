project("member"
	LANGUAGES CXX)

file(GLOB_RECURSE MEMBER_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("member" STATIC
	${MEMBER_SOURCE_FILES})
target_include_directories("member"
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries("member"
	PUBLIC "string")