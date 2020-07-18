#ifndef BIA_CONNECTOR_STACK_ITERATOR_HPP_
#define BIA_CONNECTOR_STACK_ITERATOR_HPP_

#include <bia/gc/stack_view.hpp>
#include <bia/util/gsl.hpp>
#include <cstdint>
#include <iterator>

namespace bia {
namespace connector {

template<typename DestType, bool Reverse>
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
		if (Reverse) {
			--_ptr;
		} else {
			++_ptr;
		}

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

		if (Reverse) {
			--_ptr;
		} else {
			++_ptr;
		}

		return copy;
	}
	stack_iterator& operator--() noexcept
	{
		if (Reverse) {
			++_ptr;
		} else {
			--_ptr;
		}

		return *this;
	}
	stack_iterator operator--(int) noexcept
	{
		stack_iterator copy{ _ptr };

		if (Reverse) {
			++_ptr;
		} else {
			--_ptr;
		}

		return copy;
	}
	stack_iterator& operator+=(difference_type n) noexcept
	{
		if (Reverse) {
			_ptr -= n;
		} else {
			_ptr += n;
		}

		return *this;
	}
	stack_iterator& operator-=(difference_type n) noexcept
	{
		if (Reverse) {
			_ptr += n;
		} else {
			_ptr -= n;
		}

		return *this;
	}
	stack_iterator operator+(difference_type n) const noexcept
	{
		return stack_iterator{ Reverse ? _ptr - n : _ptr + n };
	}
	template<typename T, bool R>
	friend stack_iterator<T, R> operator+(difference_type n, stack_iterator<T, R> it) noexcept;
	stack_iterator operator-(difference_type n) const noexcept
	{
		return stack_iterator{ Reverse ? _ptr + n : _ptr - n };
	}
	difference_type operator-(stack_iterator other) const noexcept
	{
		return Reverse ? other._ptr - _ptr : _ptr - other._ptr;
	}
	reference operator[](difference_type i) const noexcept
	{
		return static_cast<DestType*>((Reverse ? _ptr + i : _ptr - i)->get());
	}
	bool operator<(stack_iterator other) const noexcept
	{
		return Reverse ? _ptr > other._ptr : _ptr < other._ptr;
	}
	bool operator>(stack_iterator other) const noexcept
	{
		return Reverse ? _ptr < other._ptr : _ptr > other._ptr;
	}
	bool operator<=(stack_iterator other) const noexcept
	{
		return Reverse ? _ptr >= other._ptr : _ptr <= other._ptr;
	}
	bool operator>=(stack_iterator other) const noexcept
	{
		return Reverse ? _ptr <= other._ptr : _ptr >= other._ptr;
	}

private:
	pointer _ptr;
};

template<typename DestType, bool Reverse>
inline stack_iterator<DestType, Reverse>
    operator+(typename stack_iterator<DestType, Reverse>::difference_type n,
              stack_iterator<DestType, Reverse> it)
{
	return it + n;
}

} // namespace connector
} // namespace bia

#endif
