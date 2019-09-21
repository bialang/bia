file(GLOB TEST_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable("gctest" ${TEST_SOURCE_FILES})
target_link_libraries("gctest" "gc")
target_include_directories("gctest"
	PRIVATE ${CATCH_INCLUDE_DIRS})