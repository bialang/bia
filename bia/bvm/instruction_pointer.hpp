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

/**
 * Manages the input bytecode stream.
 */
class instruction_pointer
{
public:
	typedef const util::byte* buffer_type;

	/**
	 * Constructor.
	 *
	 * @param instructions the byte instructions
	 */
	instruction_pointer(util::span<buffer_type> instructions) noexcept
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
	/**
	 * @return the next opcode
	 * @see read()
	 */
	bytecode::op_code_type next_op_code()
	{
		return read<bytecode::op_code_type>();
	}
	/**
	 * Advances the instruction pointer.
	 *
	 * @exception error::exception
	 * 	- error::code::out_of_bounds if the new cursor is out of bounds
	 * @param offset the offset in bytes
	 * @return `*this`
	 */
	instruction_pointer& operator+=(std::int32_t offset)
	{
		_cursor += offset;
		if (_cursor < _instructions.begin() || _cursor > _instructions.end()) {
			BIA_THROW(error::code::out_of_bounds);
		}
		return *this;
	}
	/**
	 * @return the current cursor
	*/
	std::size_t cursor() const noexcept
	{
		return static_cast<std::size_t>(_cursor - _instructions.begin());
	}
	/**
	 * @return `true` if this object is valid, otherwise `false`
	 */
	operator bool() const noexcept
	{
		return _cursor + bytecode::max_instruction_size < _instructions.end();
	}

private:
	util::span<buffer_type> _instructions;
	buffer_type _cursor;
};

} // namespace bvm
} // namespace bia

#endif
