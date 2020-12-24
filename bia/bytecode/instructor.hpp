#ifndef BIA_BYTECODE_INSTRUCTOR_HPP_
#define BIA_BYTECODE_INSTRUCTOR_HPP_

#include "op_code.hpp"

#include <bia/util/portable/stream.hpp>
#include <bia/util/type_traits/equals_any.hpp>
#include <cstdint>
#include <ostream>
#include <type_traits>

namespace bia {
namespace bytecode {

template<typename Element>
class Instructor
{
public:
	template<Op_code op_code, Op_code... others>
	using is_op_code = util::type_traits::equals_any<Op_code, op_code, others...>;

	Instructor(std::ostream& output) noexcept : _output{ output }
	{}
	template<Op_code op_code>
	typename std::enable_if<is_op_code<op_code, oc_push>::value>::type write(Element value)
	{
		util::portable::write(_output, op_code);
		util::portable::write(_output, value);
	}
	template<Op_code op_code>
	typename std::enable_if<is_op_code<op_code, oc_pop>::value>::type write(std::uint8_t count)
	{
		util::portable::write(_output, op_code);
		util::portable::write(_output, count);
	}
	template<Op_code op_code>
	typename std::enable_if<is_op_code<op_code, oc_mov>::value>::type write(std::uint8_t index, Element value)
	{
		util::portable::write(_output, op_code);
		util::portable::write(_output, index);
		util::portable::write(_output, value);
	}
	std::ostream& output() noexcept
	{
		return _output;
	}

private:
	std::ostream& _output;
};

} // namespace bytecode
} // namespace bia

#endif
