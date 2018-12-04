cmake_minimum_required(VERSION 3.1)

add_executable(architectureTest architecture_test.cpp test_main.cpp)
target_link_libraries(architectureTest Bia)

add_test(ArchitectureInstructionTest architectureTest instruction-test)
add_test(ArchitectureTest architectureTest)