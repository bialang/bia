cmake_minimum_required(VERSION 3.1)

project(examples
	LANGUAGES CXX C)

add_executable(hello_world "hello_world.cpp")
target_link_libraries(hello_world PUBLIC bsl compiler)

add_executable(showcase "showcase.cpp")
target_link_libraries(showcase PUBLIC bsl compiler)

add_executable(hello_world_c "hello_world.c")
target_link_libraries(hello_world_c PUBLIC cbia)

