#ifndef BIA_BYTECODE_WRITER_INSTRUCTION_HPP_
#define BIA_BYTECODE_WRITER_INSTRUCTION_HPP_

#include "../op_code.hpp"
#include "common.hpp"
#include "member.hpp"

#include <ostream>
#include <type_traits>
#include <util/portable/stream.hpp>
#include <util/type_traits/equals_any.hpp>
#include <util/type_traits/int_maker.hpp>

namespace bia {
namespace bytecode {
namespace writer {

class instruction
{
public:
	template<op_code Op_code, op_code... Others>
	using is_op_code = util::type_traits::equals_any<op_code, Op_code, Others...>;

	instruction(std::ostream& output) noexcept : _output(output)
	{}
	template<bool Optimize, op_code Op_code>
	typename std::enable_if<is_op_code<Op_code, oc_return_void>::value>::type write()
	{
		optimized_write<false>(_output, Op_code);
	}
	template<bool Optimize, op_code Op_code, typename P0>
	typename std::enable_if<is_op_code<Op_code, oc_jump, oc_jump_false, oc_jump_true>::value &&
	                        is_parameter_size<P0>::value &&
	                        std::is_signed<typename std::decay<P0>::type>::value>::type
	    write(P0 p0)
	{
		optimized_write<false>(_output, static_cast<op_code>(Op_code - parameter_size_index<Optimize>(p0)));
		optimized_write<Optimize>(_output, p0);
	}
	template<bool Optimize, op_code Op_code, typename P0>
	typename std::enable_if<is_op_code<Op_code, oc_test>::value && is_member_source<P0>::value>::type
	    write(P0 p0)
	{
		optimized_write<false>(_output, static_cast<op_code>(Op_code - member_source_index<Optimize>(p0)));
		optimized_member<Optimize>(_output, p0);
	}
	template<bool Optimize, op_code Op_code, typename P0>
	typename std::enable_if<is_op_code<Op_code, oc_invoke>::value && is_member_source<P0>::value>::type
	    write(P0 p0, std::uint8_t p1)
	{
		optimized_write<false>(_output, static_cast<op_code>(Op_code - member_source_index<Optimize>(p0)));
		optimized_member<Optimize>(_output, p0);
		optimized_write<false>(_output, p1);
	}
	template<bool Optimize, op_code Op_code, typename P0, typename P1>
	typename std::enable_if<is_op_code<Op_code, oc_instantiate>::value && is_member_destination<P0>::value &&
	                        is_constant<P1>::value>::type
	    write(P0 p0, P1 p1)
	{
		optimized_write<false>(
		    _output, static_cast<op_code>(Op_code - member_destination_index<Optimize>(p0) * mdo_count -
		                                  constant_index<Optimize>(p1)));
		optimized_member<Optimize>(_output, p0);
		optimized_write<Optimize>(_output, p1);
	}
	void finish()
	{
		_forward_end(
		    util::type_traits::template int_filler<
		        op_code, (max_instruction_size / sizeof(op_code) + sizeof(op_code)), oc_return_void>::values);
	}

private:
	std::ostream& _output;

	template<op_code... Ints>
	void _forward_end(util::type_traits::int_container<op_code, Ints...>)
	{
		util::portable::write(_output, Ints...);
	}
};

} // namespace writer
} // namespace bytecode
} // namespace bia

#endif