#pragma once

#include "op_code.hpp"

#include <cstdint>
#include <stream/output_stream.hpp>
#include <util/limit_checker.hpp>
#include <util/type_traits/equals_any.hpp>
#include <util/type_traits/int_maker.hpp>

namespace bia {
namespace bytecode {

class instruction_writer
{
public:
	instruction_writer(stream::output_stream& output) noexcept : output(output)
	{}

	template<bool Optimize, OP_CODE Op_code>
	typename std::enable_if<util::type_traits::equals_any<OP_CODE, Op_code, OC_RETURN_VOID>::value != 0>::type
		write_instruction()
	{
		output.write_all(Op_code);
	}
	template<bool Optimize, OP_CODE Op_code, typename P0>
	typename std::enable_if<
		util::type_traits::equals_any<OP_CODE, Op_code, OC_JUMP, OC_JUMP_TRUE, OC_JUMP_FALSE>::value != 0>::type
		write_instruction(P0 p0)
	{
		output.write_all(static_cast<OP_CODE>(Op_code - index_of_immediate_int<Optimize>(p0)));
		optimize<Optimize>(p0);
	}
	template<bool Optimize, OP_CODE Op_code, typename P0>
	typename std::enable_if<
		util::type_traits::equals_any<OP_CODE, Op_code, OC_PUSH_IMMEDIATE, OC_RETURN_IMMEDIATE>::value != 0>::type
		write_instruction(P0 p0)
	{
		output.write_all(static_cast<OP_CODE>(Op_code - index_of_immediate<Optimize>(p0)));
		optimize<Optimize>(p0);
	}
	template<bool Optimize, OP_CODE Op_code, typename P0>
	typename std::enable_if<
		util::type_traits::equals_any<OP_CODE, Op_code, OC_PUSH_MEMBER, OC_RETURN_MEMBER, OC_TEST>::value != 0>::type
		write_instruction(P0 p0)
	{
		output.write_all(static_cast<OP_CODE>(Op_code - index_of_member<Optimize>(p0)));
		optimize<Optimize>(p0.index);
	}
	template<bool Optimize, OP_CODE Op_code, typename P0, typename P1>
	typename std::enable_if<util::type_traits::equals_any<OP_CODE, Op_code, OC_INSTANTIATE>::value != 0>::type
		write_instruction(P0 p0, P1 p1)
	{
		auto offset = index_of_member<Optimize>(p0) * IOCO_COUNT + index_of_immediate<Optimize>(p1);

		output.write_all(static_cast<OP_CODE>(Op_code - offset));
		optimize<Optimize>(p0.index);
		optimize<Optimize>(p1);
	}
	template<bool Optimize, OP_CODE Op_code, typename P0, typename P1>
	typename std::enable_if<
		util::type_traits::equals_any<OP_CODE, Op_code, OC_SHALLOW_COPY, OC_DEEP_COPY, OC_REFER>::value != 0>::type
		write_instruction(P0 p0, P1 p1)
	{
		auto offset = index_of_member<Optimize>(p0) * MOCO_COUNT + index_of_member<Optimize>(p1);

		output.write_all(static_cast<OP_CODE>(Op_code - offset));
		optimize<Optimize>(p0.index);
		optimize<Optimize>(p1.index);
	}
	template<bool Optimize, OP_CODE Op_code, typename P0, typename P1, typename P2, typename P3>
	typename std::enable_if<util::type_traits::equals_any<OP_CODE, Op_code, OC_CALL>::value != 0>::type
		write_instruction(P0 p0, P1 p1, P2 p2, P3 p3)
	{
		auto offset = ((index_of_member<Optimize>(p0) * MOCO_COUNT + index_of_member<Optimize>(p1)) * IIOCO_COUNT +
					   index_of_immediate_int<Optimize>(p2)) *
						  IIOCO_COUNT +
					  index_of_immediate_int<Optimize>(p3);

		output.write_all(static_cast<OP_CODE>(Op_code - offset));
		optimize<Optimize>(p0.index);
		optimize<Optimize>(p1.index);
		optimize<Optimize>(p2);
		optimize<Optimize>(p3);
	}
	void write_end()
	{
		forward_end(util::type_traits::int_filler<op_code_type,
												  (max_instruction_size / sizeof(op_code_type) + sizeof(op_code_type)),
												  OC_RETURN_VOID>::values);
	}

private:
	stream::output_stream& output;

	template<op_code_type... Ints>
	void forward_end(util::type_traits::int_container<op_code_type, Ints...>)
	{
		output.write_all(Ints...);
	}
	template<bool Optimize, typename T>
	typename std::enable_if<util::type_traits::equals_any_type<T, std::int8_t, std::int32_t, std::int64_t, std::uint8_t,
															   std::uint32_t>::value != 0>::type
		optimize(T value)
	{
		if (Optimize) {
			if (std::is_unsigned<T>::value) {
				if (util::limit_checker<std::uint8_t>::check(value)) {
					output.write_all(static_cast<std::uint8_t>(value));
				} else {
					output.write_all(value);
				}
			} else {
				if (util::limit_checker<std::int8_t>::check(value)) {
					output.write_all(static_cast<std::int8_t>(value));
				} else if (util::limit_checker<std::int32_t>::check(value)) {
					output.write_all(static_cast<std::int32_t>(value));
				} else {
					output.write_all(value);
				}
			}
		} else {
			output.write_all(value);
		}
	}
	template<bool Optimize, typename T>
	typename std::enable_if<util::type_traits::equals_any_type<T, std::int8_t, std::int32_t>::value != 0,
							IMMEDIATE_INT_OP_CODE_OPTION>::type
		index_of_immediate_int(T value) noexcept
	{
		constexpr auto index = util::type_traits::equals_any_type<T, std::int8_t, std::int32_t>::value;

		if (Optimize) {
			if (util::limit_checker<std::int8_t>::check(value)) {
				return IIOCO_INT8;
			}
		}

		return static_cast<IMMEDIATE_INT_OP_CODE_OPTION>(index - 1);
	}
	template<bool Optimize, typename T>
	typename std::enable_if<util::type_traits::equals_any_type<T, std::int8_t, std::int32_t, std::int64_t>::value != 0,
							IMMEDIATE_OP_CODE_OPTION>::type
		index_of_immediate(T value) noexcept
	{
		constexpr auto index = util::type_traits::equals_any_type<T, std::int8_t, std::int32_t, std::int64_t>::value;

		if (Optimize) {
			if (util::limit_checker<std::int8_t>::check(value)) {
				return IOCO_INT8;
			} else if (util::limit_checker<std::int32_t>::check(value)) {
				return IOCO_INT32;
			}
		}

		return static_cast<IMMEDIATE_OP_CODE_OPTION>(index - 1);
	}
	template<bool Optimize, typename T>
	typename std::enable_if<util::type_traits::equals_any_type<T, double, test_register, string_index>::value != 0,
							IMMEDIATE_OP_CODE_OPTION>::type
		index_of_immediate(T value) noexcept
	{
		constexpr auto index = util::type_traits::equals_any_type<T, double, test_register, string_index>::value;

		return static_cast<IMMEDIATE_OP_CODE_OPTION>(index + 2);
	}
	template<bool Optimize, typename T>
	MEMBER_OP_CODE_OPTION index_of_member(T value) noexcept
	{
		constexpr auto index = util::type_traits::equals_any_type<T, temp_member_index<std::uint8_t>,
																  temp_member_index<std::uint32_t>>::value;

		static_assert(index != 0, "invalid member type");

		if (Optimize) {
			if (util::limit_checker<std::uint8_t>::check(value.index)) {
				return MOCO_TINY_TEMP;
			}
		}

		return static_cast<MEMBER_OP_CODE_OPTION>(index - 1);
	}
};

} // namespace bytecode
} // namespace bia