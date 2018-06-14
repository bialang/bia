#pragma once

#include <cstdint>


namespace bia
{
namespace framework
{

typedef uint32_t operator_type;

enum OPERATOR : operator_type
{
	/** The `=` operator. */
	O_ASSIGN = 0x3d,

	/** The `+` operator. */
	O_PLUS = 0x2b,
	/** The `-` operator. */
	O_MINUS = 0x2d,
	/** The `/` operator. */
	O_DIVIDE = 0x2f,
	/** The `%` operator. */
	O_MODULUS = 0x25,
	/** The `*` operator. */
	O_MULTIPLY = 0x2a,
	/** The `+=` operator. */
	O_ASSIGN_PLUS = 0x3d2b,
	/** The `-=` operator. */
	O_ASSIGN_MINUS = 0x3d2d,
	/** The `/=` operator. */
	O_ASSIGN_DIVIDE = 0x3d2f,
	/** The `%=` operator. */
	O_ASSIGN_MODULUS = 0x3d25,
	/** The `*=` operator. */
	O_ASSIGN_MULTIPLY = 0x3d2a,

	/** The `|` operator. */
	O_BITWISE_OR = 0x7c,
	/** The `&` operator. */
	O_BITWISE_AND = 0x26,
	/** The `^` operator. */
	O_BITWISE_XOR = 0x5e,
	/** The `~` operator. */
	O_BITWISE_INVERT = 0x7e,
	/** The `<<` operator. */
	O_BITWISE_ARITHMETIC_LEFT_SHIFT = 0x3c3c,
	/** The `>>` operator. */
	O_BITWISE_ARITHMETIC_RIGHT_SHIFT = 0x3e3e,
	/** The `>>>` operator. */
	O_BITWISE_LOGICAL_RIGHT_SHIFT = 0x3e3e3e,
	/** The `|=` operator. */
	O_BITWISE_ASSIGN_OR = 0x3d7c,
	/** The `&=` operator. */
	O_BITWISE_ASSIGN_AND = 0x3d26,
	/** The `^=` operator. */
	O_BITWISE_ASSIGN_XOR = 0x3d5e,
	/** The `<<=` operator. */
	O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT = 0x3d3c3c,
	/** The `>>=` operator. */
	O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT = 0x3d3e3e,
	/** The `>>>=` operator. */
	O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT = 0x3d3e3e3e,

	/** The `==` operator. */
	O_EQUALS = 0x3d3d,
	/** The `!=` operator. */
	O_EQUALS_NOT = 0x213d,
	/** The `<` operator. */
	O_LESS_THAN = 0x3c,
	/** The `<=` operator. */
	O_LESS_EQUALS = 0x3c3d,
	/** The `>` operator. */
	O_GREATER_THAN = 0x3e,
	/** The `>=` operator. */
	O_GREATER_EQUALS = 0x3e3d,
};

}
}