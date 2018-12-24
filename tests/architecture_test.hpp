#pragma once

#include <architecture.hpp>

#include "test.hpp"


class architecture_test
{
public:
	static void instruction_test();
	static void test_move();
	static void test_add();
	static void test_sub();
	static void test_jump();
	static void test_push();
	static void test_pop();
	static void test_function_call();
	static void test_other();
};
