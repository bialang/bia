#include "big_int_test.hpp"

#include <big_int_allocator.hpp>
#include <limits>
#include <cstdint>


BEGIN_DECLARE_TESTS
test::add("set_get", &big_int_test::test_set_get);
test::add("add", &big_int_test::test_add);
test::add("sub", &big_int_test::test_sub);
test::add("mul", &big_int_test::test_mul);
test::add("div", &big_int_test::test_div);
test::add("power", &big_int_test::test_power);
END_DECLARE_TESTS

big_int_test::big_int_test() : _builder(&_allocator)
{
	bia::machine::memory::big_int_allocator::initialize(std::shared_ptr<simple_allocator>(&_allocator, [](simple_allocator*) {}));
}

void big_int_test::test_set_get()
{
	_int.set(0);

	test::template assert_equals<int64_t>(_int.to_int(), 0, "=0");

	_int.set(1);

	test::template assert_equals<int64_t>(_int.to_int(), 1, "=1");

	_int.set(-1);

	test::template assert_equals<int64_t>(_int.to_int(), -1, "=-1");

	_int.set(std::numeric_limits<int64_t>::max());

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::max(), "=max(int64)");

	_int.set(std::numeric_limits<int64_t>::min());

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::min(), "=min(int64)");

	// Out of range
	_int.set("9223372036854775808");

	try {
		_int.to_int();

		test::fail("Int should overflow.");
	} catch (const bia::exception::overflow_error&) {}

	_int.set("-9223372036854775809");

	try {
		_int.to_int();

		test::fail("Int should underflow.");
	} catch (const bia::exception::overflow_error&) {}
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

	// Big ints
	_int.set("88398457280934820934823923454263544625344402803");
	_int.add(big_int("649824346253415929384534425344265443624346283426434523"));
	_int.to_string(_builder);

	test::assert_equals(_builder.buffer<char>(), "649824434651873210319355360168188897887890908770837326", "88398457280934820934823923454263544625344402803-649824346253415929384534425344265443624346283426434523");

	_int.set("88398457280934820934823923454263544625344402803");
	_int.add(big_int("-649824346253415929384534425344265443624346283426434523"));
	_int.to_string(_builder);

	test::assert_equals(_builder.buffer<char>(), "-649824257854958648449713490520341989360801658082031720", "88398457280934820934823923454263544625344402803- (-649824346253415929384534425344265443624346283426434523)");
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

	// Big ints
	_int.set("88398457280934820934823923454263544625344402803");
	_int.subtract(big_int("649824346253415929384534425344265443624346283426434523"));
	_int.to_string(_builder);

	test::assert_equals(_builder.buffer<char>(), "-649824257854958648449713490520341989360801658082031720", "88398457280934820934823923454263544625344402803-649824346253415929384534425344265443624346283426434523");

	_int.set("88398457280934820934823923454263544625344402803");
	_int.subtract(big_int("-649824346253415929384534425344265443624346283426434523"));
	_int.to_string(_builder);

	test::assert_equals(_builder.buffer<char>(), "649824434651873210319355360168188897887890908770837326", "88398457280934820934823923454263544625344402803- (-649824346253415929384534425344265443624346283426434523)");
}

void big_int_test::test_mul()
{
	_int.set(0);
	_int.multiply(std::numeric_limits<int64_t>::max());

	test::template assert_equals<int64_t>(_int.to_int(), 0, "0 * max(int64)");

	_int.set(1);
	_int.multiply(std::numeric_limits<int64_t>::max());

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::max(), "1 * max(int64)");

	_int.set(0);
	_int.multiply(std::numeric_limits<int64_t>::min());

	test::template assert_equals<int64_t>(_int.to_int(), 0, "0 * min(int64)");

	_int.set(1);
	_int.multiply(std::numeric_limits<int64_t>::min());

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::min(), "1 * min(int64)");

	// Sign checking
	_int.set(153092023);
	_int.multiply(60247241209);

	test::template assert_equals<int64_t>(_int.to_int(), 153092023 * 60247241209, "153092023 * 60247241209");

	_int.set(-536870912);
	_int.multiply(17179869184);

	test::template assert_equals<int64_t>(_int.to_int(), -536870912 * 17179869184, "-536870912 * 17179869184");

	_int.set(536870912);
	_int.multiply(-17179869184);

	test::template assert_equals<int64_t>(_int.to_int(), 536870912 * -17179869184, "536870912 * (-17179869184)");

	_int.set(-153092023);
	_int.multiply(-60247241209);

	test::template assert_equals<int64_t>(_int.to_int(), -153092023 * -60247241209, "-153092023 * (-60247241209)");

	// Big integers
	_int.set(153092024);
	_int.multiply(60247241209);

	try {
		_int.to_int();

		test::fail("Integer should overflow.");
	} catch (const bia::exception::overflow_error&) {
		_int.to_string(_builder);

		test::assert_equals(_builder.buffer<char>(), "9223372097102017016", "153092024 * 60247241209");
	}

	_int.set(536870913);
	_int.multiply(-17179869184);

	try {
		_int.to_int();

		test::fail("Integer should underflow.");
	} catch (const bia::exception::overflow_error&) {
		_int.to_string(_builder);

		test::assert_equals(_builder.buffer<char>(), "-9223372054034644992", "536870913 * (-17179869184)");
	}

	_int.set("9223372097102017016");
	_int.multiply("-9223372054034644992");
	_int.to_string(_builder);

	test::assert_equals(_builder.buffer<char>(), "-85070592444373661784923993466703183872", "9223372097102017016 * (-9223372054034644992)");
}

void big_int_test::test_div()
{
	_int.set(1);

	try {
		_int.divide(0);

		test::fail("Division by zero should fail.");
	} catch (const bia::exception::zero_division_error&) {}

	_int.set(std::numeric_limits<int64_t>::max());
	_int.divide(1);

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::max(), "max(int64) / 1");

	_int.set(std::numeric_limits<int64_t>::min());
	_int.divide(1);

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::min(), "min(int64) / 1");

	// Sign checking
	_int.set(std::numeric_limits<int64_t>::max());
	_int.divide(60247241209);

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::max() / 60247241209, "max(int64) / 60247241209");

	_int.set(std::numeric_limits<int64_t>::min());
	_int.divide(17179869184);

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::min() / 17179869184, "min(int64) / 17179869184");

	_int.set(std::numeric_limits<int64_t>::min());
	_int.divide(-17179869184);

	test::template assert_equals<int64_t>(_int.to_int(), std::numeric_limits<int64_t>::min() / -17179869184, "min(int64) / (-17179869184)");

	// Big integers
	_int.set("555682719864735315808193871872");
	_int.divide(60247241209);

	try {
		_int.to_int();

		test::fail("Integer should overflow.");
	} catch (const bia::exception::overflow_error&) {
		_int.to_string(_builder);

		test::assert_equals(_builder.buffer<char>(), "9223372036854775808", "555682719864735315808193871872 / 60247241209");
	}

	_int.set("158456325028528675204267769856");
	_int.divide(-17179869184);

	try {
		_int.to_int();

		test::fail("Integer should underflow.");
	} catch (const bia::exception::overflow_error&) {
		_int.to_string(_builder);

		test::assert_equals(_builder.buffer<char>(), "-9223372036854775809", "158456325028528675204267769856 / (-17179869184)");
	}

	_int.set("-590295810358705651712");
	_int.divide("9895665555555845132");

	test::template assert_equals<int64_t>(_int.to_int(), -59, "-590295810358705651712 / 9895665555555845132");
}

void big_int_test::test_power()
{
	_int.set(2);
	_int.power(4096);
	_int.to_string(_builder);

	test::assert_equals(_builder.buffer<char>(), "1044388881413152506691752710716624382579964249047383780384233483283953907971557456848826811934997558340890106714439262837987573438185793607263236087851365277945956976543709998340361590134383718314428070011855946226376318839397712745672334684344586617496807908705803704071284048740118609114467977783598029006686938976881787785946905630190260940599579453432823469303026696443059025015972399867714215541693835559885291486318237914434496734087811872639496475100189041349008417061675093668333850551032972088269550769983616369411933015213796825837188091833656751221318492846368125550225998300412344784862595674492194617023806505913245610825731835380087608622102834270197698202313169017678006675195485079921636419370285375124784014907159135459982790513399611551794271106831134090584272884279791554849782954323534517065223269061394905987693002122963395687782878948440616007412945674919823050571642377154816321380631045902916136926708342856440730447899971901781465763473223850267253059899795996090799469201774624817718449867455659250178329070473119433165550807568221846571746373296884912819520317457002440926616910874148385078411929804522981857338977648103126085903001302413467189726673216491511131602920781738033436090243804708340403154190336", "2**4096");

	_int.set(-2);
	_int.power(4096);
	_int.to_string(_builder);

	test::assert_equals(_builder.buffer<char>(), "1044388881413152506691752710716624382579964249047383780384233483283953907971557456848826811934997558340890106714439262837987573438185793607263236087851365277945956976543709998340361590134383718314428070011855946226376318839397712745672334684344586617496807908705803704071284048740118609114467977783598029006686938976881787785946905630190260940599579453432823469303026696443059025015972399867714215541693835559885291486318237914434496734087811872639496475100189041349008417061675093668333850551032972088269550769983616369411933015213796825837188091833656751221318492846368125550225998300412344784862595674492194617023806505913245610825731835380087608622102834270197698202313169017678006675195485079921636419370285375124784014907159135459982790513399611551794271106831134090584272884279791554849782954323534517065223269061394905987693002122963395687782878948440616007412945674919823050571642377154816321380631045902916136926708342856440730447899971901781465763473223850267253059899795996090799469201774624817718449867455659250178329070473119433165550807568221846571746373296884912819520317457002440926616910874148385078411929804522981857338977648103126085903001302413467189726673216491511131602920781738033436090243804708340403154190336", "-2**4096");

	_int.set(-2);
	_int.power(4097);
	_int.to_string(_builder);

	test::assert_equals(_builder.buffer<char>(), "-2088777762826305013383505421433248765159928498094767560768466966567907815943114913697653623869995116681780213428878525675975146876371587214526472175702730555891913953087419996680723180268767436628856140023711892452752637678795425491344669368689173234993615817411607408142568097480237218228935955567196058013373877953763575571893811260380521881199158906865646938606053392886118050031944799735428431083387671119770582972636475828868993468175623745278992950200378082698016834123350187336667701102065944176539101539967232738823866030427593651674376183667313502442636985692736251100451996600824689569725191348984389234047613011826491221651463670760175217244205668540395396404626338035356013350390970159843272838740570750249568029814318270919965581026799223103588542213662268181168545768559583109699565908647069034130446538122789811975386004245926791375565757896881232014825891349839646101143284754309632642761262091805832273853416685712881460895799943803562931526946447700534506119799591992181598938403549249635436899734911318500356658140946238866331101615136443693143492746593769825639040634914004881853233821748296770156823859609045963714677955296206252171806002604826934379453346432983022263205841563476066872180487609416680806308380672", "-2**4097");
}
