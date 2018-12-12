#include "big_int_test.hpp"

#include <limits>
#include <cstdint>

BEGIN_DECLARE_TESTS
	test::add("add", &big_int_test::test_add);
  test::add("sub", &big_int_test::test_sub);
END_DECLARE_TESTS

void big_int_test::arithmetic_test()
{
  big_int_test _tester;

  _tester.test_add();
	_tester.test_sub();
}

void big_int_test::test_add()
{
	_int.set(659);
  _int.add(95565);

  test::template assert_equals<int64_t>(_int.to_int(), 659 + 95565, "659 + 95565");

  _int.set(695);
  _int.add(-9965);

  test::template assert_equals<int64_t>(_int.to_int(), 695 - 9965, "695 + (-9965)");

	_int.set(-695);
  _int.add(-9965);

  test::template assert_equals<int64_t>(_int.to_int(), -695 - 9965, "-695 + (-9965)");

	// Check limits of 32 bit
	_int.set(-695);
	_int.add(std::numeric_limits<int32_t>::max());

	test::template assert_equals<int64_t>(_int.to_int(), -695 + std::numeric_limits<int32_t>::max(), "-695 + max(int32)");

  _int.set(695);
  _int.add(std::numeric_limits<int32_t>::min());

  test::template assert_equals<int64_t>(_int.to_int(), 695 + std::numeric_limits<int32_t>::min(), "695 + min(int32)");

	// Check limits of 64 bit
	_int.set(-695);
	_int.add(std::numeric_limits<int64_t>::max());

	test::template assert_equals<int64_t>(_int.to_int(), -695LL + std::numeric_limits<int64_t>::max(), "-695 + max(int64)");

  _int.set(695);
  _int.add(std::numeric_limits<int64_t>::min());

  test::template assert_equals<int64_t>(_int.to_int(), 695LL + std::numeric_limits<int64_t>::min(), "695 + min(int64)");
}

void big_int_test::test_sub()
{
	_int.set(659);
	_int.subtract(95565);

	test::template assert_equals<int64_t>(_int.to_int(), 659 - 95565, "659 - 95565");

	_int.set(695);
	_int.subtract(-9965);

	test::template assert_equals<int64_t>(_int.to_int(), 695 + 9965, "695 - (-9965)");

	_int.set(-695);
	_int.subtract(-9965);

	test::template assert_equals<int64_t>(_int.to_int(), -695 + 9965, "-695 - (-9965)");

	// Check limits of 32 bit
	_int.set(-695);
	_int.subtract(std::numeric_limits<int32_t>::max());

	test::template assert_equals<int64_t>(_int.to_int(), -695LL - std::numeric_limits<int32_t>::max(), "-695 - max(int32)");

	_int.set(695);
	_int.subtract(std::numeric_limits<int32_t>::min());

	test::template assert_equals<int64_t>(_int.to_int(), 695LL - std::numeric_limits<int32_t>::min(), "695 - min(int32)");

	// Check limits of 64 bit
	_int.set(695);
	_int.subtract(std::numeric_limits<int64_t>::max());

	test::template assert_equals<int64_t>(_int.to_int(), 695LL - std::numeric_limits<int64_t>::max(), "695 - max(int64)");

	_int.set(-695);
	_int.subtract(std::numeric_limits<int64_t>::min());

	test::template assert_equals<int64_t>(_int.to_int(), -695LL - std::numeric_limits<int64_t>::min(), "-695 - min(int64)");
}
