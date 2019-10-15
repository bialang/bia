project("bvm"
	LANGUAGES CXX)

create_library(STATIC
	PUBLIC "member"
	PUBLIC "compiler")

file(GLOB BLA "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
add_executable("bla" ${BLA})
target_link_libraries("bla" "bvm")
