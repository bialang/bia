cmake_minimum_required(VERSION 3.1)

project(bia_examples
	LANGUAGES CXX C)

add_executable(hello_world "hello_world.cpp")
target_link_libraries(hello_world
	PUBLIC bia::bia)

add_executable(showcase "showcase.cpp")
target_link_libraries(showcase
	PUBLIC bia::bia)

add_executable(hello_world_c "hello_world.c")
target_link_libraries(hello_world_c
	PUBLIC bia::bia)


# playground
add_executable(playground++ "playground.cpp" "${BACKWARD_ENABLE}")
target_link_libraries(playground++
	PUBLIC bia::bia)
add_executable(playground "playground.c" "${BACKWARD_ENABLE}")
target_link_libraries(playground
	PUBLIC bia::bia)

if(BACKWARD_ENABLE)
	add_backward(playground++)
	add_backward(playground)
endif()
