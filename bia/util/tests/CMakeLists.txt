file(GLOB TEST_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable("utiltest" ${TEST_SOURCE_FILES})
target_link_libraries("utiltest" "util" Catch2::Catch2)

catch_discover_tests("utiltest")