#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

#include <cstdint>

namespace bia {
namespace bytecode {

typedef std::uint8_t Op_code_type;

enum Op_code : Op_code_type
{
	/// (Element) - pushes the argument on top of the native stack
	oc_push,
	/// (std::uint8_t) - pops n given elements from the native stack
	oc_pop,
	/// (std::uint8_t, Element) - moves the given element to the specified position (relative to the base)
	oc_mov,

	/// (std::uint8_t) - calls the object at the specified location on the advanced stack
	oc_call
};

} // namespace bytecode
} // namespace bia

#endif
