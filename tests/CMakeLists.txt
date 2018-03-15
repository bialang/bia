cmake_minimum_required(VERSION 3.1)

enable_testing()

add_executable(MathExpressionTest testMathExpression.cpp)
target_link_libraries(MathExpressionTest Bia)

add_test(MathExpressionTestConstant MathExpressionTest)

#add_executable(testa test.cpp)
#set_target_properties(testa PROPERTIES COMPILE_DEFINITIONS BUILDER_STATIC_DEFINE)
#target_link_libraries(testa Bia)
#enable_testing()
#add_test(testa testa)