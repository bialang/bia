#include "test.hpp"

#include <machine_context.hpp>
#include <buffer_input_stream.hpp>
#include <string>

using namespace bia;
using namespace std::string_literals;


class bia_sanity_test
{
public:
	bia_sanity_test() : _context(test_allocator::shared_allocator(), test_allocator::shared_member_allocator(), test_allocator::shared_big_int_allocator(), test_allocator::shared_executable_allocator())
	{
		// Setup
	}

	void test_compile()
	{
		std::unique_ptr<stream::buffer_input_stream> _script;

		_script.reset(new stream::buffer_input_stream(to_input_stream(R"(var i = 0)")));

		try {
			_context.execute(*_script);
		} catch (const exception::bia_error & e) {
			test::fail("execute() failed: "s + e.what());
		}

		_script.reset(new stream::buffer_input_stream(to_input_stream(R"(var i = 0)")));

		try {
			_context.add_script("test", *_script);
		} catch (const exception::bia_error & e) {
			test::fail("add_script() failed: "s + e.what());
		}

		try {
			_context.get_script("test");
		} catch (const exception::bia_error & e) {
			test::fail("get_script() failed: "s + e.what());
		}
	}
	void test_member_interface()
	{

	}

private:
	machine::machine_context _context;

	static stream::buffer_input_stream to_input_stream(const char * _code)
	{
		return stream::buffer_input_stream(std::shared_ptr<const int8_t>(reinterpret_cast<const int8_t*>(_code), [](const int8_t * _buffer) {}), std::char_traits<char>::length(_code));
	}
};

BEGIN_DECLARE_TESTS
test::add("compile", &bia_sanity_test::test_compile);
END_DECLARE_TESTS