#include <catch.hpp>
#include <string/encoding/standard/ascii.hpp>

using namespace bia::string::encoding;
using namespace bia::string::encoding::standard;

template<typename T>
inline void test_encoding(encoder* enc, const T* string, const char32_t* characters)
{
	code_point cp = 0;
	auto begin    = reinterpret_cast<const std::int8_t*>(string);
	auto end      = begin + std::char_traits<T>::length(string) + 1;

	while (begin < end) {
		REQUIRE(enc->next(begin, end, cp));
		REQUIRE(cp == *characters++);
	}

	REQUIRE_FALSE(enc->next(begin, end, cp));
}

TEST_CASE("standard ascii encoder", "[string][encoder][standard]")
{
	auto enc = encoder::get_instance(encoder::STANDARD_ENCODING::ASCII);

	SECTION("correct encoding")
	{
		test_encoding(enc, "Hello!", U"Hello!");
	}

	SECTION("invalid character")
	{
		const std::int8_t buffer[] = { static_cast<std::int8_t>(0xaa) };
		code_point cp              = 0;
		auto begin                 = buffer;
		auto end                   = buffer + sizeof(buffer);

		REQUIRE_THROWS_AS(enc->next(begin, end, cp), bia::exception::char_encoding_exception);
	}

	encoder::free_instance(enc);
}

TEST_CASE("standard utf8 encoder", "[string][encoder][standard]")
{
	auto enc = encoder::get_instance(encoder::STANDARD_ENCODING::UTF_8);

	SECTION("ascii")
	{
		test_encoding(enc, "Hello!", U"Hello!");
	}

	SECTION("correct encoding")
	{
		test_encoding(enc, u8"じゅういちがつ", U"じゅういちがつ");
	}

	SECTION("invalid character")
	{
		/*const std::int8_t buffer[] = { static_cast<std::int8_t>(0xaa) };
		code_point cp			   = 0;
		auto begin				   = buffer;
		auto end				   = buffer + sizeof(buffer);

		REQUIRE_THROWS_AS(enc->next(begin, end, cp), bia::exception::char_encoding_exception);*/
	}

	encoder::free_instance(enc);
}