#ifndef BIA_GC_MEMORY_ITERATOR_HPP_
#define BIA_GC_MEMORY_ITERATOR_HPP_

#include "std_allocator.hpp"

#include <exception/implementation_error.hpp>
#include <cstdint>
#include <iterator>
#include <memory>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace gc {
namespace memory {

typedef std::vector<util::byte*, std_allocator<util::byte*>> page_container_type;

class iterator
{
public:
	typedef std::random_access_iterator_tag iterator_category;
	typedef util::byte value_type;
	typedef std::ptrdiff_t difference_type;
	typedef const value_type* pointer;
	typedef value_type reference;

	iterator(util::not_null<std::shared_ptr<page_container_type>> pages, std::size_t page_size,
	         std::size_t index, std::size_t offset)
	    : _pages(std::move(pages.get()))
	{
		BIA_EXPECTS(offset < page_size && index < _pages->size());

		_page_size = page_size;
		_index     = index;
		_offset    = offset;
	}
	iterator(const iterator& copy) = default;
	int compare(const iterator& other) const
	{
		BIA_EXPECTS(_pages == other._pages);

		const auto left  = _index * _page_size + _offset;
		const auto right = other._index * other._page_size + other._offset;

		return left < right ? -1 : (left > right ? 1 : 0);
	}
	bool operator==(const iterator& other) const
	{
		return compare(other) == 0;
	}
	bool operator!=(const iterator& other) const
	{
		return compare(other) != 0;
	}
	bool operator<(const iterator& other) const
	{
		return compare(other) < 0;
	}
	bool operator>(const iterator& other) const
	{
		return compare(other) > 0;
	}
	bool operator<=(const iterator& other) const
	{
		return compare(other) <= 0;
	}
	bool operator>=(const iterator& other) const
	{
		return compare(other) >= 0;
	}
	iterator& operator++()
	{
		if (++_offset == _page_size) {
			_offset = 0;

			++_index;
		}

		return *this;
	}
	iterator operator++(int)
	{
		auto copy = *this;

		this->operator++();

		return copy;
	}
	iterator& operator--()
	{
		if (!_offset--) {
			_offset = _page_size - 1;

			--_index;
		}

		return *this;
	}
	iterator operator--(int)
	{
		auto copy = *this;

		this->operator--();

		return copy;
	}
	iterator& operator+=(difference_type diff)
	{
		BIA_IMPLEMENTATION_ERROR("not implemented");

		return *this;
	}
	iterator& operator-=(difference_type diff)
	{
		BIA_IMPLEMENTATION_ERROR("not implemented");
		
		return *this;
	}
	iterator operator+(difference_type diff) const
	{
		auto copy = *this;

		copy += diff;

		return copy;
	}
	iterator operator-(difference_type diff) const
	{
		auto copy = *this;

		copy -= diff;

		return copy;
	}
	difference_type operator-(const iterator& other) const
	{
		return (_index * _page_size + _offset) - (other._index * other._page_size + other._offset);
	}
	friend iterator operator+(difference_type diff, const iterator& right)
	{
		return right + diff;
	}
	iterator& operator=(const iterator& copy) = default;
	reference operator[](difference_type diff)
	{
		return this->operator*();
	}
	reference operator*() const
	{
		return (*_pages)[_index][_offset];
	}

private:
	std::shared_ptr<page_container_type> _pages;
	std::size_t _page_size;
	std::size_t _offset;
	std::size_t _index;
};

} // namespace memory
} // namespace gc
} // namespace bia

#endif