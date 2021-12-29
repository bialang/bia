#include <bia/internal/type/definition.hpp>
#include <bia/internal/type/integral.hpp>
#include <catch2/catch.hpp>
#include <cstdint>
#include <type_traits>

using namespace bia;
using namespace bia::internal::type;

template<typename First, typename Second>
inline int compare()
{
	Definition<First> first;
	Definition<Second> second;
	return first.compare(&second);
}

TEST_CASE("definitions", "[internal]")
{
	SECTION("integrals")
	{
		REQUIRE(
		  compare<char,
		          typename std::conditional<std::is_signed<char>::value, signed char, unsigned char>::type>() ==
		  0);
		REQUIRE(compare<bool, signed char>() != 0);
		REQUIRE(compare<bool, unsigned char>() != 0);

#if defined(__cpp_char8_t)
		REQUIRE(compare<char8_t, unsigned char>() == 0);
#endif
		REQUIRE(compare<char16_t, std::uint_least16_t>() == 0);
		REQUIRE(compare<char32_t, std::uint_least32_t>() == 0);

		if (sizeof(int) == sizeof(short)) {
			REQUIRE(compare<int, short>() == 0);
			REQUIRE(compare<unsigned int, unsigned short>() == 0);
		}

		if (sizeof(short) == sizeof(long)) {
			REQUIRE(compare<short, long>() == 0);
			REQUIRE(compare<unsigned short, unsigned long>() == 0);
		}

		if (sizeof(int) == sizeof(long)) {
			REQUIRE(compare<int, long>() == 0);
			REQUIRE(compare<unsigned int, unsigned long>() == 0);
		}

		if (sizeof(short) == sizeof(long long)) {
			REQUIRE(compare<short, long long>() == 0);
			REQUIRE(compare<unsigned short, unsigned long long>() == 0);
		}

		if (sizeof(int) == sizeof(long long)) {
			REQUIRE(compare<int, long long>() == 0);
			REQUIRE(compare<unsigned int, unsigned long long>() == 0);
		}

		if (sizeof(long) == sizeof(long long)) {
			REQUIRE(compare<long, long long>() == 0);
			REQUIRE(compare<unsigned long, unsigned long long>() == 0);
		}
	}
}
