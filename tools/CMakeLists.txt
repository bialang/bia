cmake_minimum_required(VERSION 3.1)

project(bia-tool
	VERSION 0.0.0
	LANGUAGES CXX)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/config.hpp")

file(GLOB_RECURSE sources
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(bia_tool "${sources}" "${BACKWARD_ENABLE}")
target_link_libraries(bia_tool PRIVATE bia::bia)
target_include_directories(bia_tool
	PRIVATE "${CMAKE_SOURCE_DIR}/dependencies/CLI11/include/")
set_target_properties(bia_tool
	PROPERTIES OUTPUT_NAME "bia")

if(BACKWARD_ENABLE)
	add_backward(bia_tool)
endif()

install(TARGETS bia_tool
	RUNTIME DESTINATION "bin")
