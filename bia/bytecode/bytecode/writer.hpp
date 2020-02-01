#ifndef BIA_BYTECODE_WRITER_HPP_
#define BIA_BYTECODE_WRITER_HPP_

#include "op_code.hpp"

#include <cstdint>
#include <ostream>
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
	typename std::enable_if<util::type_traits::equals_any<op_code, Op_code, oc_return_void>::value != 0>::type
	    write_instruction()
	{
		_optimize_write<false>(_output, Op_code);
	}
	/**
	 * Writes instructions with one parameter to the output. Valid @ref op_code: @ref oc_jump, @ref
	 * oc_jump_false and @ref oc_jump_true
	 *
	 * @param p0 the first parameter
	 * @throw see _optimize_write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam Op_code the op code
	 * @tparam P0 the type of the first parameter, see _index_of_iioco()
	 */
	template<bool Optimize, op_code Op_code, typename P0>
	typename std::enable_if<util::type_traits::equals_any<op_code, Op_code, oc_jump, oc_jump_false,
	                                                      oc_jump_true>::value != 0>::type
	    write_instruction(P0 p0)
	{
		_optimize_write<false>(_output, static_cast<op_code>(Op_code - _index_of_iioco<Optimize>(p0)));
		_optimize_write<Optimize>(p0);
	}
	/**
	 * Writes instructions with one parameter to the output. Valid @ref op_code: @ref oc_push_immediate and
	 * @ref oc_return_immediate
	 *
	 * @param p0 the first parameter
	 * @throw see _optimize_write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam Op_code the op code
	 * @tparam P0 the type of the first parameter, see _index_of_ioco()
	 */
	template<bool Optimize, op_code Op_code, typename P0>
	typename std::enable_if<util::type_traits::equals_any<op_code, Op_code, oc_push_immediate,
	                                                      oc_return_immediate>::value != 0>::type
	    write_instruction(P0 p0)
	{
		_optimize_write<false>(static_cast<op_code>(Op_code - _index_of_ioco<Optimize>(p0)));
		_optimize_write<Optimize>(p0);
	}
	/**
	 * Writes instructions with one parameter to the output. Valid @ref op_code: @ref oc_push_member, @ref
	 * oc_return_member and @ref oc_test
	 *
	 * @param p0 the first parameter
	 * @throw see _optimize_write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam Op_code the op code
	 * @tparam P0 the type of the first parameter, see _index_of_moco()
	 */
	template<bool Optimize, op_code Op_code, typename P0>
	typename std::enable_if<util::type_traits::equals_any<op_code, Op_code, oc_push_member, oc_return_member,
	                                                      oc_test>::value != 0>::type
	    write_instruction(P0 p0)
	{
		_optimize_write<false>(static_cast<op_code>(Op_code - _index_of_moco<Optimize>(p0)));
		_optimize_write<Optimize>(p0.index);
	}
	/**
	 * Writes instructions with two parameter to the output. Valid @ref op_code: @ref oc_instantiate
	 *
	 * @param p0 the first parameter
	 * @param p1 the second parameter
	 * @throw see _optimize_write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam Op_code the op code
	 * @tparam P0 the type of the first parameter, see _index_of_moco()
	 * @tparam P1 the type of the second parameter, see _index_of_ioco()
	 */
	template<bool Optimize, op_code Op_code, typename P0, typename P1>
	typename std::enable_if<util::type_traits::equals_any<op_code, Op_code, oc_instantiate>::value != 0>::type
	    write_instruction(P0 p0, P1 p1)
	{
		auto offset = _index_of_moco<Optimize>(p0) * ioco_count + _index_of_ioco<Optimize>(p1);

		_optimize_write<false>(static_cast<op_code>(Op_code - offset));
		_optimize_write<Optimize>(p0.index);
		_optimize_write<Optimize>(p1);
	}
	/**
	 * Writes instructions with two parameter to the output. Valid @ref op_code: @ref oc_shallow_copy, @ref
	 * oc_deep_copy and @ref oc_refer
	 *
	 * @param p0 the first parameter
	 * @param p1 the second parameter
	 * @throw see _optimize_write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam Op_code the op code
	 * @tparam P0 the type of the first parameter, see _index_of_moco()
	 * @tparam P1 the type of the second parameter, see _index_of_moco()
	 */
	template<bool Optimize, op_code Op_code, typename P0, typename P1>
	typename std::enable_if<util::type_traits::equals_any<op_code, Op_code, oc_shallow_copy, oc_deep_copy,
	                                                      oc_refer>::value != 0>::type
	    write_instruction(P0 p0, P1 p1)
	{
		auto offset = _index_of_moco<Optimize>(p0) * moco_count + _index_of_moco<Optimize>(p1);

		_optimize_write<false>(static_cast<op_code>(Op_code - offset));
		_optimize_write<Optimize>(p0.index);
		_optimize_write<Optimize>(p1.index);
	}
	/**
	 * Writes instructions with four parameter to the output. Valid @ref op_code: @ref oc_call
	 *
	 * @param p0 the first parameter
	 * @param p1 the second parameter
	 * @param p2 the third parameter
	 * @param p3 the fourth parameter
	 * @throw see _optimize_write()
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam Op_code the op code
	 * @tparam P0 the type of the first parameter, see _index_of_moco()
	 * @tparam P1 the type of the second parameter, see _index_of_moco()
	 * @tparam P2 the type of the second parameter, see _index_of_iioco()
	 * @tparam P3 the type of the second parameter, see _index_of_iioco()
	 */
	template<bool Optimize, op_code Op_code, typename P0, typename P1, typename P2, typename P3>
	typename std::enable_if<util::type_traits::equals_any<op_code, Op_code, oc_call>::value != 0>::type
	    write_instruction(P0 p0, P1 p1, P2 p2, P3 p3)
	{
		auto offset =
		    ((index_of_member<Optimize>(p0) * moco_count + index_of_member<Optimize>(p1)) * iioco_count +
		     _index_of_iioco<Optimize>(p2)) *
		        iioco_count +
		    _index_of_iioco<Optimize>(p3);

		_optimize_write<false>(static_cast<op_code>(Op_code - offset));
		_optimize_write<Optimize>(p0.index);
		_optimize_write<Optimize>(p1.index);
		_optimize_write<Optimize>(p2);
		_optimize_write<Optimize>(p3);
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
				if (util::limit_checker<std::uint8_t>::check(value)) {
					util::portable::write(_output, static_cast<std::uint8_t>(value));
				} else {
					util::portable::write(_output, value);
				}
			} else {
				if (util::limit_checker<std::int8_t>::check(value)) {
					util::portable::write(_output, static_cast<std::int8_t>(value));
				} else if (util::limit_checker<std::int32_t>::check(value)) {
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
	/**
	 * Returns the index of @ref immediate_int_op_code_option type.
	 *
	 * @param value the value
	 * @returns the index
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam T the type of the value; allowed types are `std::int8_t` and `std::int32_t`
	 */
	template<bool Optimize, typename T>
	typename std::enable_if<util::type_traits::equals_any_type<T, std::int8_t, std::int32_t>::value != 0,
	                        immediate_int_op_code_option>::type
	    _index_of_iioco(T value) noexcept
	{
		constexpr auto index = util::type_traits::equals_any_type<T, std::int8_t, std::int32_t>::value;

		if (Optimize) {
			if (util::limit_checker<std::int8_t>::check(value)) {
				return iioco_int8;
			}
		}

		return static_cast<immediate_int_op_code_option>(index - 1);
	}
	/**
	 * Returns the index of @ref immediate_op_code_option type.
	 *
	 * @param value the value
	 * @returns the index
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam T the type of the value; allowed types are `std::int8_t`, `std::int32_t` and `std::int64_t`
	 */
	template<bool Optimize, typename T>
	typename std::enable_if<
	    util::type_traits::equals_any_type<T, std::int8_t, std::int32_t, std::int64_t>::value != 0,
	    immediate_op_code_option>::type
	    _index_of_ioco(T value) noexcept
	{
		constexpr auto index =
		    util::type_traits::equals_any_type<T, std::int8_t, std::int32_t, std::int64_t>::value;

		if (Optimize) {
			if (util::limit_checker<std::int8_t>::check(value)) {
				return ioco_int8;
			} else if (util::limit_checker<std::int32_t>::check(value)) {
				return ioco_int32;
			}
		}

		return static_cast<immediate_op_code_option>(index - 1);
	}
	/**
	 * Returns the index of @ref immediate_op_code_option type.
	 *
	 * @param value the value
	 * @returns the index
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam T the type of the value; allowed types are @ref test_register and @ref string_index
	 */
	template<bool Optimize, typename T>
	typename std::enable_if<
	    util::type_traits::equals_any_type<T, double, test_register, string_index>::value != 0,
	    immediate_op_code_option>::type
	    _index_of_ioco(T value) noexcept
	{
		constexpr auto index =
		    util::type_traits::equals_any_type<T, double, test_register, string_index>::value;

		return static_cast<immediate_op_code_option>(index + 2);
	}
	/**
	 * Returns the index of @ref member_op_code_option type.
	 *
	 * @param value the value
	 * @returns the index
	 * @tparam Optimize whether the op code size should be optimized
	 * @tparam T the type of the value; allowed types are @ref temp_member_index
	 */
	template<bool Optimize, typename T>
	typename std::enable_if<util::type_traits::equals_any_type<T, temp_member_index<std::uint8_t>,
	                                                           temp_member_index<std::uint32_t>>::value,
	                        member_op_code_option>::type
	    _index_of_moco(T value) noexcept
	{
		constexpr auto index = util::type_traits::equals_any_type<T, temp_member_index<std::uint8_t>,
		                                                          temp_member_index<std::uint32_t>>::value;

		if (Optimize) {
			if (util::limit_checker<std::uint8_t>::check(value.index)) {
				return moco_tiny_temp;
			}
		}

		return static_cast<member_op_code_option>(index - 1);
	}
};

} // namespace bytecode
} // namespace bia

#endif