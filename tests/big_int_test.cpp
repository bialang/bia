#include "big_int_test.hpp"

#include <big_int.hpp>


using namespace bia::dependency;

BEGIN_DECLARE_TESTS
	test::add("test_add", &big_int_test::arithmetic_test);
//  test::add("add_test", &big_int_test::add_test);
END_DECLARE_TESTS

void big_int_test::arithmetic_test()
{
  big_int_test _tester;

  _tester.test_add();
}

void big_int_test::test_add()
{
  big_int _tmp(659);

  _tmp.add(big_int(95565));

  test::template assert_equals<int64_t>(_tmp.to_int(), 659 + 95565, "659 + 95565");

  _tmp.~big_int();
  new(&_tmp) big_int(695);
  _tmp.add(big_int(-9965));

  test::template assert_equals<int64_t>(_tmp.to_int(), 695 - 9965, "695 + (-9965)");
}
