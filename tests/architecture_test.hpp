#pragma once

#include <architecture.cpp>
#include <cppunit/extensions/HelperMacros.h>


class architecture_test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(architecture_test);
	CPPUNIT_TEST(test_move);
	CPPUNIT_TEST(test_add);
	CPPUNIT_TEST(test_sub);
	CPPUNIT_TEST(test_xor);
	CPPUNIT_TEST(test_jump);
	CPPUNIT_TEST(test_push);
	CPPUNIT_TEST(test_pop);
	CPPUNIT_TEST(test_function_call);
	CPPUNIT_TEST(test_other);
	CPPUNIT_TEST_SUITE_END();
	
public:
	void test_move();
	void test_add();
	void test_sub();
	void test_xor();
	void test_jump();
	void test_push();
	void test_pop();
	void test_function_call();
	void test_other();

public:
  void setUp();

protected:
  void example();
  void anotherExample();
  void testAdd();
  void testEquals();
};