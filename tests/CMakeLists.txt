#cmake_minimum_required(VERSION 3.1)

add_executable(SanityTest test.hpp testFunctions.hpp testSanity.cpp)
target_link_libraries(SanityTest Bia)

add_test(MathExpressionTestConstant SanityTest math_const)
add_test(MathExpressionTestMixed SanityTest math_mixed)
add_test(StaticFunctionTest SanityTest static_function)
add_test(TypeCastTest SanityTest type_cast)