cmake_minimum_required(VERSION 3.1)

# Architecture Test
add_executable(architectureTest test_main.cpp architecture_test.cpp)
target_link_libraries(architectureTest Bia)

#add_test(ArchitectureInstructionTest architectureTest instruction)
add_test(ArchitectureTest architectureTest)

# Big Int Test
add_executable(bigIntTest test_main.cpp big_int_test.cpp)
target_link_libraries(bigIntTest Bia)

add_test(SetGetTest bigIntTest set_get)
add_test(AddTest bigIntTest add)
add_test(SubTest bigIntTest sub)
add_test(MulTest bigIntTest mul)
add_test(DivTest bigIntTest div)
add_test(ModTest bigIntTest mod)
add_test(PowerTest bigIntTest power)
add_test(BigIntTest bigIntTest)

# Bia Sanity Test
add_executable(biaSanityTest test_main.cpp bia_sanity_test.cpp)
target_link_libraries(biaSanityTest Bia)

add_test(CompileBiaTest biaSanityTest compile)
add_test(MemberInterfaceTest biaSanityTest member_interface)
add_test(FunctionTest biaSanityTest function_order)
add_test(BiaSanityTest biaSanityTest)
