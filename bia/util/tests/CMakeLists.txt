file(GLOB_RECURSE TEST_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable("utiltest" ${TEST_SOURCE_FILES})
target_link_libraries("utiltest" "util")
target_include_directories("utiltest"
	PRIVATE ${CATCH_INCLUDE_DIRS})

add_test("util" "utiltest" ${BIA_TEST_ARGS})