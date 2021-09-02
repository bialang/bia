#ifndef BIA_BYTECODE_INSTRUCTOR_HPP_
#define BIA_BYTECODE_INSTRUCTOR_HPP_

#include "op_code.hpp"
#include "operation.hpp"

#include <bia/memory/gc/types.hpp>
#include <bia/util/contract.hpp>
#include <bia/util/portable/stream.hpp>
#include <bia/util/type_traits/equals_any.hpp>
#include <bia/util/type_traits/type_index.hpp>
#include <cstdint>
#include <ostream>
#include <type_traits>

namespace bia {
namespace bytecode {

template<Op_code op_code>
using is_with_2_operands =
  std::integral_constant<bool,
                         (op_code >= Op_code::load_from_namespace && op_code <= Op_code::ugreater_equal_than)>;

template<Op_code op_code>
using is_branch_operation =
  std::integral_constant<bool, (op_code >= Op_code::jump && op_code <= Op_code::jump_false)>;

class Instructor
{
public:
	Instructor(std::ostream& output) noexcept : _output{ output }
	{}
	template<Op_code op_code>
	typename std::enable_if<(op_code == Op_code::load_resource)>::type write(Address destination,
	                                                                         std::uint32_t index)
	{
		_write_op_code<op_code>();
		util::portable::write(_output, destination);
		util::portable::write(_output, index);
	}
	template<Op_code op_code>
	typename std::enable_if<is_with_2_operands<op_code>::value>::type write(Size size, Address first,
	                                                                        Address second)
	{
		_write_op_code<op_code>(size);
		util::portable::write(_output, first);
		util::portable::write(_output, second);
	}
	template<Op_code op_code>
	typename std::enable_if<is_branch_operation<op_code>::value>::type write(std::int32_t offset)
	{
		_write_op_code<op_code>();
		util::portable::write(_output, offset);
	}
	template<Op_code op_code, typename Type>
	typename std::enable_if<(op_code == Op_code::store)>::type write(Address destination, Type immediate)
	{
		_write_op_code<op_code>(_bytes_to_size<sizeof(typename std::decay<Type>::type)>());
		util::portable::write(_output, destination);
		util::portable::write(_output, immediate);
	}
	template<Op_code op_code>
	typename std::enable_if<(op_code == Op_code::invoke || op_code == Op_code::test)>::type
	  write(Address function)
	{
		_write_op_code<op_code>();
		util::portable::write(_output, function);
	}
	std::ostream& output() noexcept
	{
		return _output;
	}

private:
	std::ostream& _output;

	template<Op_code op_code>
	void _write_op_code(Size size = {})
	{
		util::portable::write(
		  _output, static_cast<std::uint8_t>(static_cast<int>(op_code) | (static_cast<int>(size) << 6)));
	}
	template<typename Type>
	void _write(Size size, Type value)
	{
		static_assert(std::is_trivial<Type>::value, "Type must be trivial");
		BIA_ASSERT(_size_to_bytes(size) == sizeof(Type));
		util::portable::write(_output, value);
	}
	static std::size_t _size_to_bytes(Size size)
	{
		switch (size) {
		case Size::bit_8: return 1;
		case Size::bit_16: return 2;
		case Size::bit_32: return 4;
		case Size::bit_64: return 8;
		default: BIA_THROW(error::Code::bad_switch_value);
		}
	}
	template<std::size_t Bytes>
	constexpr static Size _bytes_to_size() noexcept
	{
		static_assert(Bytes == 1 || Bytes == 2 || Bytes == 4 || Bytes == 8, "bad Bytes");
		return Bytes == 1 ? Size::bit_8 : Bytes == 2 ? Size::bit_16 : Bytes == 4 ? Size::bit_32 : Size::bit_64;
	}
};

} // namespace bytecode
} // namespace bia

#endif
