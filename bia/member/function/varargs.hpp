#ifndef BIA_MEMBER_FUNCTION_VARARGS_HPP_
#define BIA_MEMBER_FUNCTION_VARARGS_HPP_

#include <bia/memory/frame.hpp>
#include <cstddef>
#include <iterator>

namespace bia {
namespace member {
namespace function {

template<typename Type>
class Varargs
{
public:
	class Iterator
	{
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef Type value_type;
		typedef std::ptrdiff_t difference_type;
		// typedef ? pointer;
		typedef value_type reference;

		reference operator*()
		{
			return _parent->at(_index);
		}
		Iterator& operator++() noexcept
		{
			++_index;
			return *this;
		}
		Iterator operator++(int) noexcept
		{
			Iterator copy = *this;
			++copy;
			return copy;
		}
		bool operator==(const Iterator& other) const noexcept
		{
			return _index == other._index;
		}
		bool operator!=(const Iterator& other) const noexcept
		{
			return _index != other._index;
		}

	private:
		template<typename>
		friend class Varargs;
		std::ptrdiff_t _index;
		Varargs* _parent;

		Iterator(std::ptrdiff_t index, Varargs* parent) noexcept : _index{ index }, _parent{ parent }
		{}
	};

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
	Iterator begin()
	{
		return { 0, this };
	}
	Iterator end()
	{
		return { _count, this };
	}

private:
	memory::Frame<false> _frame;
	std::ptrdiff_t _count;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
