#include "test.hpp"

#include <bia.hpp>
#include <machine_context.hpp>
#include <buffer_input_stream.hpp>
#include <string>

using namespace bia;
using namespace bia::machine;
using namespace std::string_literals;


class bia_sanity_test
{
public:
	static void test_compile()
	{
		auto _context = create_context();
		std::unique_ptr<stream::buffer_input_stream> _script(new stream::buffer_input_stream(to_input_stream(R"(var ci = 0)")));

		machine_context::unset_active_context();

		try {
			_context->execute(*_script);
		} catch (const exception::bia_error & e) {
			test::fail("execute() failed: "s + e.what());
		}

		_script.reset(new stream::buffer_input_stream(to_input_stream(R"(var ci = 0)")));
		machine_context::unset_active_context();

		try {
			_context->add_script("test", *_script);
		} catch (const exception::bia_error & e) {
			test::fail("add_script() failed: "s + e.what());
		}

		machine_context::unset_active_context();

		try {
			_context->get_script("test");
		} catch (const exception::bia_error & e) {
			test::fail("get_script() failed: "s + e.what());
		}

		machine_context::unset_active_context();
		_context.reset();
	}
	static void test_member_interface()
	{
		// Test interface
		auto _context = create_context();

		machine_context::unset_active_context();
		_context->template emplace_member<bia::framework::native::big_int_member>("mi0", 7852);
		machine_context::unset_active_context();

		auto _member = _context->get_member("mi0");

		machine_context::unset_active_context();

		test::template assert_equals<int64_t>(*_member->template cast<int64_t>(), 7852, "mi0 == 7852");

		// Test script
		auto _script = to_input_stream(R"(var mi1 = 61; var mi2 = mi0)");

		machine_context::unset_active_context();
		_context->execute(_script);
		machine_context::unset_active_context();

		_member = _context->get_member("mi1");

		machine_context::unset_active_context();

		test::template assert_equals<int64_t>(*_member->template cast<int64_t>(), 61, "mi1 == 61");

		machine_context::unset_active_context();

		_member = _context->get_member("mi2");

		machine_context::unset_active_context();

		test::template assert_equals<int64_t>(*_member->template cast<int64_t>(), 7852, "mi2 == mi0 == 7852");

		machine_context::unset_active_context();
		_context.reset();
	}

private:
	static std::unique_ptr<machine_context> create_context()
	{
		return std::make_unique<machine_context>(test_allocator::shared_allocator(),
			test_allocator::shared_member_allocator(),
			test_allocator::shared_big_int_allocator(),
			test_allocator::shared_executable_allocator());
	}
	static stream::buffer_input_stream to_input_stream(const char * _code)
	{
		return stream::buffer_input_stream(std::shared_ptr<const int8_t>(reinterpret_cast<const int8_t*>(_code), [](const int8_t * _buffer) {}), std::char_traits<char>::length(_code));
	}
};

BEGIN_DECLARE_TESTS
test::add("compile", &bia_sanity_test::test_compile);
test::add("member_interface", &bia_sanity_test::test_member_interface);
END_DECLARE_TESTS