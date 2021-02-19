#ifndef BIA_BVM_INSTRUCTION_POINTER_HPP_
#define BIA_BVM_INSTRUCTION_POINTER_HPP_

#include <bia/bytecode/op_code.hpp>
#include <bia/error/exception.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/portable/memory.hpp>
#include <cstddef>
#include <cstdint>

namespace bia {
namespace bvm {

struct Operation
{
	bytecode::Op_code op_code;
	std::uint8_t variation : 2;
};

/// Manages the input bytecode stream.
class Instruction_pointer
{
public:
	/**
	 * Constructor.
	 *
	 * @param instructions the byte instructions
	 */
	Instruction_pointer(util::Span<const util::Byte*> instructions) noexcept
	{
		_instructions = instructions;
		_cursor       = instructions.begin();
	}
	/**
	 * Reads the requested type from the instruction buffer.
	 *
	 * @pre this object must be valid
	 * @tparam Type the type
	 * @return the read value
	 */
	template<typename Type>
	Type read()
	{
		BIA_EXPECTS(*this);

		const auto x = util::portable::read<Type>(_cursor);
		_cursor += sizeof(Type);
		return x;
	}
	/// Reads the next op code. The cursor will advance.
	Operation fetch_and_decode()
	{
		const auto code = read<typename std::underlying_type<bytecode::Op_code>::type>();
		return Operation{ bytecode::read_op_code(code), bytecode::get_op_code_size(code) };
	}
	/**
	 * Advances the instruction pointer.
	 *
	 * @exception error::exception
	 * 	- error::code::out_of_bounds if the new cursor is out of bounds
	 * @param offset the offset in bytes
	 * @return `*this`
	 */
	Instruction_pointer& operator+=(std::int32_t offset)
	{
		_cursor += offset;
		if (_cursor < _instructions.begin() || _cursor > _instructions.end()) {
			BIA_THROW(error::Code::out_of_bounds);
		}
		return *this;
	}
	/// The current cursor position.
	std::size_t cursor() const noexcept
	{
		return static_cast<std::size_t>(_cursor - _instructions.begin());
	}
	/// Checks whether enough space is available for a complete instruction.
	operator bool() const noexcept
	{
		return _cursor < _instructions.end();
	}

private:
	util::Span<const util::Byte*> _instructions;
	const util::Byte* _cursor;
};

} // namespace bvm
} // namespace bia

#endif
