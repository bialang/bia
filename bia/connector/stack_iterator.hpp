#ifndef BIA_CONNECTOR_STACK_ITERATOR_HPP_
#define BIA_CONNECTOR_STACK_ITERATOR_HPP_

#include <bia/gc/stack_view.hpp>
#include <bia/util/gsl.hpp>
#include <cstdint>
#include <iterator>

namespace bia {
namespace connector {

template<typename DestType>
class stack_iterator
{
public:
	typedef gc::stack_view::element_type element_type;
	typedef DestType* value_type;
	typedef value_type reference;
	typedef element_type* pointer;
	typedef std::ptrdiff_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	stack_iterator() noexcept
	{
		_ptr = nullptr;
	}
	stack_iterator(pointer ptr) noexcept
	{
		_ptr = ptr;
	}
	reference operator*() const noexcept
	{
		return static_cast<DestType*>(_ptr->get());
	}
	stack_iterator& operator++() noexcept
	{
		++_ptr;

		return *this;
	}
	bool operator==(stack_iterator other) const noexcept
	{
		return _ptr == other._ptr;
	}
	bool operator!=(stack_iterator other) const noexcept
	{
		return _ptr != other._ptr;
	}
	value_type operator->() const noexcept
	{
		return static_cast<DestType*>(_ptr->get());
	}
	stack_iterator operator++(int) noexcept
	{
		stack_iterator copy{ _ptr };

		++_ptr;

		return copy;
	}
	stack_iterator& operator--() noexcept
	{
		--_ptr;

		return *this;
	}
	stack_iterator operator--(int) noexcept
	{
		stack_iterator copy{ _ptr };

		--_ptr;

		return copy;
	}
	stack_iterator& operator+=(difference_type n) noexcept
	{
		_ptr += n;

		return *this;
	}
	stack_iterator& operator-=(difference_type n) noexcept
	{
		_ptr -= n;

		return *this;
	}
	stack_iterator operator+(difference_type n) const noexcept
	{
		return stack_iterator{ _ptr + n };
	}
	template<typename T>
	friend stack_iterator<T> operator+(difference_type n, stack_iterator<T> it) noexcept;
	stack_iterator operator-(difference_type n) const noexcept
	{
		return stack_iterator{ _ptr - n };
	}
	difference_type operator-(stack_iterator other) const noexcept
	{
		return _ptr - other._ptr;
	}
	reference operator[](difference_type i) const noexcept
	{
		return static_cast<DestType*>(_ptr[i].get());
	}
	bool operator<(stack_iterator other) const noexcept
	{
		return _ptr < other._ptr;
	}
	bool operator>(stack_iterator other) const noexcept
	{
		return _ptr > other._ptr;
	}
	bool operator<=(stack_iterator other) const noexcept
	{
		return _ptr <= other._ptr;
	}
	bool operator>=(stack_iterator other) const noexcept
	{
		return _ptr >= other._ptr;
	}

private:
	pointer _ptr;
};

template<typename DestType>
inline stack_iterator<DestType> operator+(typename stack_iterator<DestType>::difference_type n,
                                        stack_iterator<DestType> it)
{
	return stack_iterator<DestType>{ n + it._ptr };
}

} // namespace connector
} // namespace bia

#endif
