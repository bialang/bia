cmake_minimum_required(VERSION 3.1)

add_executable(architectureTest test_main.cpp architecture_test.cpp)
target_link_libraries(architectureTest Bia)

add_test(ArchitectureInstructionTest architectureTest instruction_test)
add_test(ArchitectureTest architectureTest)
