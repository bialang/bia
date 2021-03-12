#ifndef BIA_BYTECODE_INSTRUCTOR_HPP_
#define BIA_BYTECODE_INSTRUCTOR_HPP_

#include "op_code.hpp"
#include "operation.hpp"

#include <bia/memory/gc/types.hpp>
#include <bia/util/portable/stream.hpp>
#include <bia/util/type_traits/equals_any.hpp>
#include <bia/util/type_traits/type_index.hpp>
#include <cstdint>
#include <ostream>
#include <type_traits>

namespace bia {
namespace bytecode {

class Instructor
{
public:
	template<Op_code op_code, Op_code... others>
	using is_op_code = util::type_traits::equals_any<Op_code, op_code, others...>;
	template<typename Type>
	using is_2_bit_variant =
	  util::type_traits::equals_any_type<Type, std::int8_t, std::int16_t, std::int32_t, std::int64_t,
	                                     std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t>;

	Instructor(std::ostream& output) noexcept : _output{ output }
	{}
	template<Op_code op_code>
	typename std::enable_if<is_op_code<op_code, Op_code::booleanize>::value>::type write(std::int32_t arg)
	{
		util::portable::write(_output, op_code);
		util::portable::write(_output, arg);
	}
	template<Op_code op_code, typename Type>
	typename std::enable_if<
	  is_op_code<op_code, Op_code::load_resource, Op_code::load_from_context>::value>::type
	  write(std::int32_t arg, std::uint32_t index)
	{
		static_assert(util::type_traits::equals_any_type<Type, memory::gc::String, memory::gc::Regex>::value,
		              "bad resource type");
		_write_2_bit_op_code_resource<op_code, Type>();
		util::portable::write(_output, arg);
		util::portable::write(_output, index);
	}
	template<Op_code op_code, typename Type>
	typename std::enable_if<is_op_code<op_code, Op_code::truthy, Op_code::falsey>::value>::type
	  write(std::int32_t arg)
	{
		static_assert(is_2_bit_variant<Type>::value, "bad truthy type");
		_write_2_bit_op_code<op_code, Type>();
		util::portable::write(_output, arg);
	}
	template<Op_code op_code>
	typename std::enable_if<is_op_code<op_code, Op_code::invoke>::value>::type write(std::int32_t arg)
	{
		util::portable::write(_output, op_code);
		util::portable::write(_output, arg);
	}
	template<Op_code op_code, typename Type>
	typename std::enable_if<is_op_code<op_code, Op_code::load>::value>::type write(std::int32_t destination,
	                                                                               Type value)
	{
		static_assert(is_2_bit_variant<Type>::value, "bad load type");
		_write_2_bit_op_code<op_code, Type>();
		util::portable::write(_output, destination);
		util::portable::write(_output, value);
	}
	template<Op_code op_code, typename Type>
	typename std::enable_if<is_op_code<op_code, Op_code::copy>::value>::type write(std::int32_t arg0,
	                                                                               std::int32_t arg1)
	{
		static_assert(is_2_bit_variant<Type>::value, "bad copy type");
		_write_2_bit_op_code<op_code, Type>();
		util::portable::write(_output, arg0);
		util::portable::write(_output, arg1);
	}
	template<Op_code op_code, typename Type>
	typename std::enable_if<is_op_code<op_code, Op_code::unsigned_raw_operation>::value>::type
	  write(Operation operation, std::int32_t arg0, std::int32_t arg1)
	{
		static_assert(is_2_bit_variant<Type>::value, "bad operation type");
		_write_2_bit_op_code<op_code, Type>();
		util::portable::write(_output, operation);
		util::portable::write(_output, arg0);
		util::portable::write(_output, arg1);
	}
	template<Op_code op_code, typename Type>
	typename std::enable_if<is_op_code<op_code, Op_code::resource_operation>::value>::type
	  write(Operation operation, std::int32_t arg0, std::int32_t arg1)
	{
		static_assert(util::type_traits::equals_any_type<Type, memory::gc::String, memory::gc::Regex>::value,
		              "bad resource type");
		_write_2_bit_op_code_resource<op_code, Type>();
		util::portable::write(_output, operation);
		util::portable::write(_output, arg0);
		util::portable::write(_output, arg1);
	}
	template<Op_code op_code, typename Offset>
	typename std::enable_if<
	  is_op_code<op_code, Op_code::jump, Op_code::jump_if_false, Op_code::jump_if_true>::value>::type
	  write(Offset offset)
	{
		static_assert(is_2_bit_variant<Offset>::value && std::is_signed<Offset>::value,
		              "bad offset type for jump operation");
		_write_2_bit_op_code<op_code, Offset>();
		util::portable::write(_output, offset);
	}
	std::ostream& output() noexcept
	{
		return _output;
	}

private:
	std::ostream& _output;

	template<Op_code op_code, typename Type>
	void _write_2_bit_op_code()
	{
		using T = typename std::make_signed<typename std::decay<Type>::type>::type;
		util::portable::write(
		  _output,
		  static_cast<Op_code>(
		    static_cast<int>(op_code) +
		    util::type_traits::type_index<T, std::int8_t, std::int16_t, std::int32_t, std::int64_t>::value));
	}
	template<Op_code op_code, typename Type>
	void _write_2_bit_op_code_resource()
	{
		util::portable::write(
		  _output, static_cast<Op_code>(
		             static_cast<int>(op_code) +
		             util::type_traits::type_index<Type, memory::gc::String, memory::gc::Regex>::value));
	}
};

} // namespace bytecode
} // namespace bia

#endif
