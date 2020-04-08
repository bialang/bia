#ifndef BIA_BYTECODE_WRITER_HPP_
#define BIA_BYTECODE_WRITER_HPP_

#include "op_code.hpp"

#include <cstdint>
#include <ostream>
#include <type_traits>
#include <util/limit_checker.hpp>
#include <util/portable/stream.hpp>
#include <util/type_traits/equals_any.hpp>
#include <util/type_traits/int_maker.hpp>

namespace bia {
namespace bytecode {

/**
 * Helper class for writing Bia bytecode to a binary stream.
 */
class instruction_writer
{
public:
	template<op_code Op_code, op_code... Op_codes>
	using is_op_code = util::type_traits::equals_any<op_code, Op_code, Op_codes...>;
	template<typename T>
	using is_member =
	    util::type_traits::equals_any_type<typename std::decay<T>::type, local_member, global_member>;
	template<typename T>
	using is_constant = util::type_traits::equals_any_type<typename std::decay<T>::type, std::int8_t,
	                                                       std::int32_t, std::int64_t, double>;
	template<typename T>
	using is_int_immediate =
	    util::type_traits::equals_any_type<typename std::decay<T>::type, std::int8_t, std::int32_t>;

	/**
	 * Constructor.
	 *
	 * @warning the output stream must be kept alive until destruction of this object
	 *
	 * @param[in] output the **binary** output stream
	 */
	instruction_writer(std::ostream& output) noexcept : _output(output)
	{}
	/**
	 * Writes parameterless instructions to the output. Valid @ref op_code: @ref oc_return_void
	 *
	 * @throw see _optimize_write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam Op_code the op code
	 */
	template<bool Optimize, op_code Op_code>
	typename std::enable_if<is_op_code<Op_code, oc_return_void>::value>::type write_instruction()
	{
		_optimize_write<false>(Op_code);
	}
	/**
	 * Writes instructions with one parameter to the output. Valid @ref op_code: @ref oc_jump, @ref
	 * oc_jump_false and @ref oc_jump_true
	 *
	 * @param p0 the first parameter
	 * @throw see _optimize_write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam Op_code the op code
	 */
	template<bool Optimize, op_code Op_code, typename P0>
	typename std::enable_if<is_op_code<Op_code, oc_jump, oc_jump_false, oc_jump_true>::value &&
	                        is_int_immediate<P0>::value>::type
	    write_instruction(P0 p0)
	{
		_optimize_write<false>(Op_code);
		_optimize_write<false>(static_cast<std::int32_t>(p0));
	}
	template<bool Optimize, op_code Op_code, typename P0, typename P1>
	typename std::enable_if<is_op_code<Op_code, oc_instantiate>::value && is_member<P0>::value &&
	                        is_constant<P1>::value>::type
	    write_instruction(P0 p0, P1 p1)
	{
		_optimize_write<false>(Op_code);
		_optimize_write<false>(static_cast<std::uint32_t>(p0.index));
		_optimize_write<false>(static_cast<std::int32_t>(p1));
	}
	/**
	 * Writes the ending sequence.
	 *
	 * @throw see _forward_end()
	 */
	void write_end()
	{
		_forward_end(util::type_traits::template int_filler<
		             op_code_type, (max_instruction_size / sizeof(op_code_type) + sizeof(op_code_type)),
		             oc_return_void>::values);
	}

private:
	/** a reference to the output stream */
	std::ostream& _output;

	/**
	 * Forwards the given ints to the output.
	 *
	 * @param ignored
	 * @throw see util::portable::write()
	 * @tparam Ints the ints that should be written
	 */
	template<op_code_type... Ints>
	void _forward_end(util::type_traits::int_container<op_code_type, Ints...>)
	{
		util::portable::write(_output, Ints...);
	}
	/**
	 * Writes the value to the output stream (if needed optimized).
	 *
	 * @param value the value
	 * @throw see util::portable::write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam T the type of the value
	 */
	template<bool Optimize, typename T>
	typename std::enable_if<
	    util::type_traits::equals_any_type<T, op_code, std::int8_t, std::int32_t, std::int64_t, std::uint8_t,
	                                       std::uint32_t>::value != 0>::type
	    _optimize_write(T value)
	{
		if (Optimize && !std::is_same<T, op_code>::value) {
			if (std::is_unsigned<T>::value) {
				if (util::limit_checker<std::uint8_t>::in_bounds(value)) {
					util::portable::write(_output, static_cast<std::uint8_t>(value));
				} else {
					util::portable::write(_output, value);
				}
			} else {
				if (util::limit_checker<std::int8_t>::in_bounds(value)) {
					util::portable::write(_output, static_cast<std::int8_t>(value));
				} else if (util::limit_checker<std::int32_t>::in_bounds(value)) {
					util::portable::write(_output, static_cast<std::int32_t>(value));
				} else {
					util::portable::write(_output, value);
				}
			}
		} // don't optimize
		else {
			util::portable::write(_output, value);
		}
	}
};

} // namespace bytecode
} // namespace bia

#endif