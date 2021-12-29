#include <bia/string/encoding/encoder.hpp>
#include <bia/util/memory_streambuf.hpp>
#include <catch2/catch.hpp>

using namespace bia::string::encoding;

template<typename Type>
inline void test_encoding(Encoder* enc, const Type* string, const char32_t* characters)
{
	bia::util::Memory_streambuf buffer{ { reinterpret_cast<const bia::util::Byte*>(string),
		                                    std::char_traits<Type>::length(string) } };
	std::istream input{ &buffer };

	while (*characters) {
		REQUIRE(enc->read(input) == static_cast<Code_point>(*characters++));
	}

	REQUIRE(enc->read(input) == Encoder::eof);
}

TEST_CASE("standard ascii encoder", "[string][encoder][standard]")
{
	const auto enc = get_encoder(Standard::ascii);

	SECTION("correct encoding")
	{
		test_encoding(enc, "Hello!", U"Hello!");
	}

	SECTION("invalid character")
	{}

	free_encoder(enc);
}

TEST_CASE("standard utf8 encoder", "[string][encoder][standard]")
{
	const auto enc = get_encoder(Standard::utf_8);

	SECTION("ascii")
	{
		test_encoding(enc, "Hello!", U"Hello!");
	}

	SECTION("correct encoding")
	{
		test_encoding(enc, u8"じゅういちがつ", U"じゅういちがつ");
		test_encoding(enc, u8"\u0001\u0079\u0080\u07ff\u0800\uffff\U00010000\U0010ffff",
		              U"\u0001\u0079\u0080\u07ff\u0800\uffff\U00010000\U0010ffff");
	}

	SECTION("invalid character")
	{}

	free_encoder(enc);
}
