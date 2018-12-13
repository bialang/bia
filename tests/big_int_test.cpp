#include "big_int_test.hpp"

#include <big_int_allocator.hpp>
#include <limits>
#include <cstdint>

BEGIN_DECLARE_TESTS
	test::add("add", &big_int_test::test_add);
  test::add("sub", &big_int_test::test_sub);
	test::add("power", &big_int_test::test_power);
END_DECLARE_TESTS

big_int_test::big_int_test() : _builder(&_allocator)
{
	bia::machine::memory::big_int_allocator::initialize(std::shared_ptr<simple_allocator>(&_allocator, [] (simple_allocator*) {puts("deleting");}));
}

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

void big_int_test::test_power()
{
	_int.set(2);
	_int.power(4096);
	_int.to_string(_builder);
	
	test::template assert_equals(_builder.buffer<char>(), "1044388881413152506691752710716624382579964249047383780384233483283953907971557456848826811934997558340890106714439262837987573438185793607263236087851365277945956976543709998340361590134383718314428070011855946226376318839397712745672334684344586617496807908705803704071284048740118609114467977783598029006686938976881787785946905630190260940599579453432823469303026696443059025015972399867714215541693835559885291486318237914434496734087811872639496475100189041349008417061675093668333850551032972088269550769983616369411933015213796825837188091833656751221318492846368125550225998300412344784862595674492194617023806505913245610825731835380087608622102834270197698202313169017678006675195485079921636419370285375124784014907159135459982790513399611551794271106831134090584272884279791554849782954323534517065223269061394905987693002122963395687782878948440616007412945674919823050571642377154816321380631045902916136926708342856440730447899971901781465763473223850267253059899795996090799469201774624817718449867455659250178329070473119433165550807568221846571746373296884912819520317457002440926616910874148385078411929804522981857338977648103126085903001302413467189726673216491511131602920781738033436090243804708340403154190336", "2**4096");
}
