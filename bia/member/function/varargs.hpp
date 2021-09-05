#ifndef BIA_MEMBER_FUNCTION_VARARGS_HPP_
#define BIA_MEMBER_FUNCTION_VARARGS_HPP_

#include <bia/memory/frame.hpp>
#include <cstddef>

namespace bia {
namespace member {
namespace function {

template<typename Type>
class Varargs
{
public:
	Varargs(memory::Frame<false> frame, std::ptrdiff_t count) : _frame{ frame }, _count{ count }
	{}
	Type at(std::size_t index)
	{
		return _frame.load<Type>(index *
		                         util::aligned(internal::type::Framer<Type>::size(), alignof(std::max_align_t)));
	}
	std::size_t size() const noexcept
	{
		return static_cast<std::size_t>(_count);
	}
	// Type* begin();
	// Type* end();

private:
	memory::Frame<false> _frame;
	std::ptrdiff_t _count;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
