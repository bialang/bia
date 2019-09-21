file(GLOB TEST_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable("gctest" ${TEST_SOURCE_FILES})
target_link_libraries("gctest" "gc" Catch2::Catch2)

catch_discover_tests("gctest")