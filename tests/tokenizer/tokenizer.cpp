#define CATCH_CONFIG_MAIN

#include <bia/gc/memory/simple_allocator.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <catch.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace bia::tokenizer;
using namespace bia::string;

class mock_receiver : public token::receiver
{
public:
	void receive(bia::util::span<const token::token*> tokens, bia::resource::manager& manager) override
	{
		for (const auto& i : tokens) {
			this->tokens.push_back(i);
		}
	}

	std::vector<token::token> tokens;
};

/*TEST_CASE("resource manager", "[tokenizer]")
{
    auto count = 0;

    {
        resource::manager rm(std::make_shared<bia::gc::memory::simple_allocator>(
                                 [&count](std::size_t s) {
                                     ++count;

                                     return std::malloc(s);
                                 },
                                 [&count](void* p) {
                                     if (p) {
                                         --count;

                                         std::free(p);
                                     }
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
}*/

TEST_CASE("tokenization", "[tokenizer]")
{
	bia_lexer lexer(std::make_shared<bia::gc::memory::simple_allocator>());
	std::stringstream code;
	auto encoder = encoding::get_encoder(encoding::standard_encoding::utf_8);
	auto finally = bia::util::make_finally([encoder] { encoding::free_encoder(encoder); });
	mock_receiver receiver;

	code << R"(let x=~false)";

	try {
		REQUIRE(code.tellg() == 0);

		lexer.lex(code, *encoder, receiver);

		REQUIRE(receiver.tokens.size() == 5);
		REQUIRE(code.eof());

		using type = token::token::type;

		REQUIRE(static_cast<type>(receiver.tokens[0].value.index()) == type::keyword);
		REQUIRE(static_cast<type>(receiver.tokens[1].value.index()) == type::identifier);
		REQUIRE(static_cast<type>(receiver.tokens[2].value.index()) == type::operator_);
		REQUIRE(static_cast<type>(receiver.tokens[3].value.index()) == type::keyword);
		REQUIRE(static_cast<type>(receiver.tokens[4].value.index()) == type::cmd_end);
	} catch (const bia::error::exception& e) {
		std::cout << "exception (ec=" << e.code() << "): " << e.what() << "\n";
		// if (dynamic_cast<const bia::exception::syntax_error*>(&e)) {
		// 	auto details = static_cast<const bia::exception::syntax_error&>(e).details();
		// 	std::cout << details.message << ":" << details.position.operator std::streamoff() << "\n\n";
		// 	std::cout << code.str() << "\n";
		// 	for (auto i = details.position.operator std::streamoff(); i--;) {
		// 		std::cout.put(' ');
		// 	}
		// 	std::cout << "\e[0;32m^\e[0;30m\n";
		// }
		FAIL("invalid syntax");
	}
}

TEST_CASE("syntax", "[tokenizer]")
{
	bia_lexer lexer(std::make_shared<bia::gc::memory::simple_allocator>());
	std::stringstream code;
	auto encoder = encoding::get_encoder(encoding::standard_encoding::utf_8);
	auto finally = bia::util::make_finally([encoder] { encoding::free_encoder(encoder); });
	mock_receiver receiver;

	constexpr char script[] = R"(
let x = false
let y=true

)";

	code << script;

	// lexer.lex(code, *encoder, receiver);

	// REQUIRE(code.tellg() == (sizeof(script) - 1));
}
