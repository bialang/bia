#ifndef BIA_TOKENIZER_TOKEN_OPERATOR_HPP_
#define BIA_TOKENIZER_TOKEN_OPERATOR_HPP_

#include <cstdint>

namespace bia {
namespace tokenizer {
namespace token {

enum class operator_type
{
	infix,
	prefix,
	postfix
};

template<std::uint8_t Precedence, std::uint8_t Variant, operator_type Type>
constexpr inline std::uint16_t make()
{
	static_assert(Precedence <= 0xf, "too high precedence");
	static_assert(Variant <= 0xf, "too high variant");

	return (Variant << 6) | (Precedence << 2) | static_cast<int>(Type);
}

enum class operator_ : std::uint16_t
{
	logical_not         = make<0, 0, operator_type::prefix>(),
	logical_or          = make<1, 0, operator_type::infix>(),
	logical_and         = make<2, 0, operator_type::infix>(),
	bitwise_or          = make<3, 0, operator_type::infix>(),
	bitwise_xor         = make<4, 0, operator_type::infix>(),
	bitwise_and         = make<5, 0, operator_type::infix>(),
	equal               = make<6, 0, operator_type::infix>(),
	not_equal           = make<6, 1, operator_type::infix>(),
	less                = make<6, 2, operator_type::infix>(),
	less_equal          = make<6, 3, operator_type::infix>(),
	greater             = make<6, 4, operator_type::infix>(),
	greater_equal       = make<6, 5, operator_type::infix>(),
	in                  = make<6, 6, operator_type::infix>(),
	bitwise_left_shift  = make<7, 0, operator_type::infix>(),
	bitwise_right_shift = make<7, 1, operator_type::infix>(),
	addition            = make<8, 0, operator_type::infix>(),
	subtraction         = make<8, 1, operator_type::infix>(),
	multiplication      = make<9, 0, operator_type::infix>(),
	division            = make<9, 1, operator_type::infix>(),
	remainder           = make<9, 2, operator_type::infix>(),
	unary_minus         = make<10, 0, operator_type::prefix>(),
	bitwise_not         = make<10, 1, operator_type::prefix>(),
	exponentation       = make<11, 0, operator_type::infix>(),
	member_access       = make<12, 0, operator_type::infix>(),
};

inline std::uint8_t precedence_of(operator_ op) noexcept
{
	return static_cast<std::uint8_t>((static_cast<std::uint16_t>(op) >> 2) & 0xf);
}

inline operator_type type_of(operator_ op) noexcept
{
	return static_cast<operator_type>(static_cast<std::uint16_t>(op) & 0x3);
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif