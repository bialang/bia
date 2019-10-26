#include <catch.hpp>
#include <stream/buffer_input_stream.hpp>
#include <string/encoding/encoder.hpp>
#include <string>
#include <tokenizer/lexer_token/constant_token.hpp>
#include <tokenizer/lexer_token/identifier_token.hpp>

using namespace bia::string::encoding;
using namespace bia::stream;
using namespace bia::tokenizer;
using namespace bia::tokenizer::lexer_token;

inline buffer_input_stream make_stream(const char* text)
{
	return buffer_input_stream(reinterpret_cast<const std::int8_t*>(text),
							   reinterpret_cast<const std::int8_t*>(text) + std::char_traits<char>::length(text));
}

TEST_CASE("bool_token", "[lexer_token][tokenizer]")
{
	auto enc = encoder::get_instance(encoder::STANDARD_ENCODING::ASCII);
	rule::parameter parameter(*enc);

	auto stream = make_stream("true");

	REQUIRE(bool_token(stream, parameter) == TOKEN_ACTION::SUCCEEDED);

	REQUIRE(stream.left_size() == 0);
	REQUIRE(parameter.bundle.begin()->type == token::TYPE::KEYWORD);
	REQUIRE(parameter.bundle.begin()->content.keyword == KEYWORD::TRUE);
}

TEST_CASE("identifier_token", "[lexer_token][tokenizer]")
{
	rule::parameter parameter(*encoder::get_instance(encoder::STANDARD_ENCODING::UTF_8));
	buffer_input_stream stream(nullptr, nullptr);

	SECTION("success")
	{
		SECTION("")
		{
			stream = make_stream(u8"i");
		}

		SECTION("")
		{
			stream = make_stream(u8"some_identifier42");
		}

		SECTION("")
		{
			stream = make_stream(u8"じゅういちがつ");
		}

		REQUIRE(identifier_token(stream, parameter) == TOKEN_ACTION::SUCCEEDED);
		REQUIRE(stream.left_size() == 0);
		REQUIRE(parameter.bundle.begin()->type == token::TYPE::IDENTIFIER);
	}

	SECTION("fail")
	{
		std::size_t size = 0;

		REQUIRE(stream.left_size() == size);
	}
}