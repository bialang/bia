#pragma once

#include <typeinfo>
#include <cstdio>
#include <cstdint>


namespace bia
{
namespace api
{
namespace framework
{

class BiaMember
{
public:
	enum OPERATORS : uint32_t
	{
		O_PLUS = 0x2b,
		O_MINUS = 0x2d,
		O_DIVIDE = 0x2f,
		O_MODULUS = 0x25,
		O_MULTIPLY = 0x2a,
		O_ASSIGN_PLUS = 0x3d2b,
		O_ASSIGN_MINUS = 0x3d2d,
		O_ASSIGN_DIVIDE = 0x3d2f,
		O_ASSIGN_MODULUS = 0x3d25,
		O_ASSIGN_MULTIPLY = 0x3d2a,

		O_BITWISE_OR = 0x7c,
		O_BITWISE_AND = 0x26,
		O_BITWISE_XOR = 0x5e,
		O_BITWISE_INVERT = 0x7e,
		O_BITWISE_ARITHMETIC_LEFT_SHIFT = 0x3c3c,
		O_BITWISE_ARITHMETIC_RIGHT_SHIFT = 0x3e3e,
		O_BITWISE_LOGICAL_RIGHT_SHIFT = 0x3e3e3e,
		O_BITWISE_ASSIGN_OR = 0x3d7c,
		O_BITWISE_ASSIGN_AND = 0x3d26,
		O_BITWISE_ASSIGN_XOR = 0x3d5e,
		O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT = 0x3d3c3c,
		O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT = 0x3d3e3e,
		O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT = 0x3d3e3e3e,

		O_EQUALS = 0x3d3d,
		O_EQUALS_NOT = 0x3d21,
		O_LESS_THAN = 0x3c,
		O_LESS_EQUALS = 0x3d3c,
		O_GREATER_THAN = 0x3e,
		O_GREATER_EQUALS = 0x3d3e,
	};

	virtual ~BiaMember() = default;


	/**
	 * Prints the contents of this object.
	 *
	 * @since	3.42.93.567
	 * @date	18-Dec-17
	*/
	inline virtual void Print()
	{
		printf("<Empty member at %p>", this);
	}
	/**
	 * Checks whether the specified type matches this object.
	 *
	 * @since	3.42.93.567
	 * @date	18-Dec-17
	 *
	 * @param	p_type	Defines the type.
	 *
	 * @return	true if they match, otherwise false.
	*/
	inline virtual bool IsType(const std::type_info & p_type) const
	{
		return false;
	}
};

}
}
}