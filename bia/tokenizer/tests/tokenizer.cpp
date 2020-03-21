#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <exception/syntax_error.hpp>
#include <gc/simple_allocator.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <tokenizer/bia_lexer.hpp>
#include <util/finally.hpp>
#include <vector>

using namespace bia::tokenizer;
using namespace bia::string;

class mock_receiver : public token::receiver
{
public:
	void receive(const token::token* begin, const token::token* end) override
	{
		while (begin != end) {
			_tokens.push_back(*begin++);
		}
	}

private:
	std::vector<token::token> _tokens;
};

TEST_CASE("resource manager", "[tokenizer]")
{
	auto count = 0;

	{
		resource::manager rm(std::make_shared<bia::gc::simple_allocator>(
		                         [&count](std::size_t s) {
			                         ++count;
			                         return std::malloc(s);
		                         },
		                         [&count](void* p) {
			                         --count;
			                         std::free(p);
		                         }),
		                     12);

		SECTION("allocate memory")
		{
			{
				const auto initial = count;
				auto buf           = rm.start_memory(false);
				std::ostream(&buf) << "hallo";

				REQUIRE(count > initial);

				rm.stop_memory(buf);
			}

			{
				const auto initial = count;
				auto buf           = rm.start_memory(false);
				std::ostream(&buf) << "12345678901";

				REQUIRE(count > initial);
			}
		}

		SECTION("restore")
		{
			const auto initial = count;
			const auto state   = rm.save_state();

			{
				auto buf = rm.start_memory(false);
				std::ostream(&buf) << "hallo";

				REQUIRE(count > initial);
			}

			const auto next = count;

			rm.restore_state(state);

			REQUIRE(count <= next);

			{
				// allocate again
				auto buf = rm.start_memory(false);
				std::ostream(&buf) << "hallo";

				REQUIRE(count == next);
			}
		}
	}

	REQUIRE(count == 0);
}

TEST_CASE("syntax", "[tokenizer]")
{
	bia_lexer lexer(std::make_shared<bia::gc::simple_allocator>());
	std::stringstream code;
	auto encoder = encoding::encoder::get_instance(encoding::encoder::standard_encoding::utf_8);
	auto finally = bia::util::make_finally([encoder] { encoding::encoder::free_instance(encoder); });
	mock_receiver receiver;

	code << R"(let x=~y)";

	try {
		lexer.lex(code, *encoder, receiver);
	} catch (const bia::exception::bia_error& e) {
		std::cout << "exception (" << e.name() << "): " << e.what() << "\n";

		if (dynamic_cast<const bia::exception::syntax_error*>(&e)) {
			auto details = static_cast<const bia::exception::syntax_error&>(e).details();

			std::cout << details.message << ":" << details.position.operator std::streamoff() << "\n\n";

			std::cout << code.str() << "\n";

			for (auto i = details.position.operator std::streamoff(); i--;) {
				std::cout.put(' ');
			}
			std::cout << "\e[0;32m^\e[0;30m\n";
		}
	}
}
