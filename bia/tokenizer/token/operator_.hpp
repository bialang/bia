#ifndef BIA_TOKENIZER_TOKEN_OPERATOR_HPP_
#define BIA_TOKENIZER_TOKEN_OPERATOR_HPP_

#include <bia/bytecode/operation.hpp>
#include <bia/error/exception.hpp>
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

template<int Precedence, std::uint8_t Variant, operator_type Type>
constexpr inline std::uint16_t make()
{
	static_assert(Precedence >= 0 && Precedence <= 0xe, "invalid precedence");
	static_assert(Variant <= 0xf, "too high variant");

	return (Variant << 6) | (Precedence << 2) | static_cast<int>(Type);
}

enum class Operator : std::uint16_t
{
	assign                      = make<0, 0, operator_type::infix>(),
	logical_or                  = make<1, 0, operator_type::infix>(),
	logical_and                 = make<2, 0, operator_type::infix>(),
	logical_not                 = make<3, 0, operator_type::prefix>(),
	equal                       = make<4, 0, operator_type::infix>(),
	not_equal                   = make<4, 1, operator_type::infix>(),
	less                        = make<4, 2, operator_type::infix>(),
	less_equal                  = make<4, 3, operator_type::infix>(),
	greater                     = make<4, 4, operator_type::infix>(),
	greater_equal               = make<4, 5, operator_type::infix>(),
	in                          = make<4, 6, operator_type::infix>(),
	three_way_comparison        = make<5, 0, operator_type::infix>(),
	bitwise_or                  = make<6, 0, operator_type::infix>(),
	bitwise_xor                 = make<7, 0, operator_type::infix>(),
	bitwise_and                 = make<8, 0, operator_type::infix>(),
	bitwise_left_shift          = make<9, 0, operator_type::infix>(),
	bitwise_right_shift         = make<9, 1, operator_type::infix>(),
	plus                        = make<10, 0, operator_type::infix>(),
	minus                       = make<10, 1, operator_type::infix>(),
	multiply                    = make<11, 0, operator_type::infix>(),
	divide                      = make<11, 1, operator_type::infix>(),
	modulus                     = make<11, 2, operator_type::infix>(),
	unary_minus                 = make<12, 0, operator_type::prefix>(),
	bitwise_not                 = make<12, 1, operator_type::prefix>(),
	exponentation               = make<13, 0, operator_type::infix>(),
	member_access               = make<14, 0, operator_type::infix>(),
	nullable_member_access      = make<14, 1, operator_type::infix>(),
	function_call_open          = make<14, 2, operator_type::prefix>(),
	nullable_function_call_open = make<14, 3, operator_type::prefix>(),
	function_call_close         = make<14, 4, operator_type::postfix>(),
};

inline int precedence_of(Operator op) noexcept
{
	return (static_cast<std::uint16_t>(op) >> 2) & 0xf;
}

inline operator_type type_of(Operator op) noexcept
{
	return static_cast<operator_type>(static_cast<std::uint16_t>(op) & 0x3);
}

inline bytecode::Infix_operation to_infix_operation(Operator op)
{
	using bytecode::Infix_operation;
	switch (op) {
	case Operator::bitwise_or: return Infix_operation::bitwise_or;
	case Operator::bitwise_xor: return Infix_operation::bitwise_xor;
	case Operator::bitwise_and: return Infix_operation::bitwise_and;
	case Operator::bitwise_left_shift: return Infix_operation::bitwise_left_shift;
	case Operator::bitwise_right_shift: return Infix_operation::bitwise_right_shift;
	case Operator::plus: return Infix_operation::addition;
	case Operator::minus: return Infix_operation::subtraction;
	case Operator::multiply: return Infix_operation::multiplication;
	case Operator::divide: return Infix_operation::division;
	case Operator::modulus: return Infix_operation::remainder;
	case Operator::exponentation: return Infix_operation::exponentation;
	default: BIA_THROW(error::Code::bad_infix_operation);
	}
}

inline bytecode::Test_operation to_test_operation(Operator op)
{
	using bytecode::Test_operation;
	switch (op) {
	case Operator::equal: return Test_operation::equal;
	case Operator::not_equal: return Test_operation::not_equal;
	case Operator::less: return Test_operation::less;
	case Operator::less_equal: return Test_operation::less_equal;
	case Operator::greater: return Test_operation::greater;
	case Operator::greater_equal: return Test_operation::greater_equal;
	case Operator::in: return Test_operation::in;
	case Operator::three_way_comparison: return Test_operation::three_way_comparison;
	default: BIA_THROW(error::Code::bad_test_operation);
	}
}

inline bytecode::Self_operation to_self_operator(Operator op)
{
	using bytecode::Self_operation;
	switch (op) {
	case Operator::unary_minus: return Self_operation::unary_minus;
	case Operator::bitwise_not: return Self_operation::bitwise_not;
	default: BIA_THROW(error::Code::bad_self_operation);
	}
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
