cmake_minimum_required(VERSION 3.1)

# Architecture Test
add_executable(architectureTest test_main.cpp architecture_test.cpp)
target_link_libraries(architectureTest Bia)

add_test(ArchitectureInstructionTest architectureTest instruction)
add_test(ArchitectureTest architectureTest)

# Big Int Test
add_executable(bigIntTest test_main.cpp big_int_test.cpp)
target_link_libraries(bigIntTest Bia)

add_test(AddTest bigIntTest add)
add_test(SubTest bigIntTest sub)
add_test(PowerTest bigIntTest power)
add_test(BigIntTest bigIntTest)
