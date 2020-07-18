
add_executable(hello_world "hello_world.cpp")
target_link_libraries(hello_world PUBLIC bsl compiler)

add_executable(showcase "showcase.cpp")
target_link_libraries(showcase PUBLIC bsl compiler)
