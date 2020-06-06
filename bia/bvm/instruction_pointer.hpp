#ifndef BIA_BVM_INSTRUCTION_POINTER_HPP_
#define BIA_BVM_INSTRUCTION_POINTER_HPP_

#include <bia/bytecode/op_code.hpp>
#include <cstddef>
#include <cstdint>
#include <bia/util/gsl.hpp>
#include <bia/util/portable/memory.hpp>

namespace bia {
namespace bvm {

class instruction_pointer
{
public:
	typedef const util::byte* buffer_type;

	instruction_pointer(util::not_null<buffer_type> first, util::not_null<buffer_type> last) noexcept
	{
		_first  = first.get();
		_last   = last.get();
		_cursor = _first;
	}
	template<typename T>
	T read()
	{
		BIA_EXPECTS(*this);

		const auto x = util::portable::read<T>(_cursor);

		_cursor += sizeof(T);

		return x;
	}
	bytecode::op_code_type next_op_code()
	{
		return read<bytecode::op_code_type>();
	}
	instruction_pointer& operator+=(std::int32_t offset)
	{
		_cursor += offset;

		if (_cursor < _first || _cursor > _last) {
			throw;
		}

		return *this;
	}
	operator bool() const noexcept
	{
		return _cursor + bytecode::max_instruction_size < _last;
	}

private:
	buffer_type _first;
	buffer_type _last;
	buffer_type _cursor;
};

} // namespace bvm
} // namespace bia

#endif
