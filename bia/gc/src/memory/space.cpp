#include "gc/memory/space.hpp"

#include <algorithm>

using namespace bia;
using namespace bia::gc::memory;

space::space(util::not_null<std::shared_ptr<allocator>> allocator, std::size_t page_size) noexcept
    : _allocator(std::move(allocator.get())),
      _pages(std::make_shared<page_container_type>(std_allocator<util::byte*>(_allocator)))
{
	_page_size = page_size;
}

space::~space()
{
	for (auto page : *_pages) {
		_allocator->deallocate(page);
	}
}

void space::move_back(std::size_t offset)
{
	BIA_EXPECTS(offset <= size());

	if (auto indices = offset / _page_size) {
		_index -= indices;
		offset -= indices * _page_size;
	}

	_offset -= offset;
}

bool space::valid() const noexcept
{
	return _allocator != nullptr;
}

std::size_t space::size() const
{
	BIA_EXPECTS(valid());

	return _offset + _index * _page_size;
}

std::size_t space::capacity() const
{
	BIA_EXPECTS(valid());

	return _pages->size() * _page_size;
}

util::not_null<util::span<util::byte>> space::next_region(std::size_t size)
{
	BIA_EXPECTS(valid());

	// go to next page
	if (_offset == _page_size) {
		_offset = 0;

		++_index;
	}

	// allocate page
	if (_pages->size() <= _index) {
		_pages->push_back(static_cast<util::byte*>(_allocator->checked_allocate(_page_size).get()));
	}

	const auto cursor = (*_pages)[_index] + _offset;

	size = std::min(_page_size - _offset, size);
	_offset += size;

	return util::span<util::byte>(cursor, size);
}

iterator space::cursor() const
{
	BIA_EXPECTS(valid());

	return { _pages, _page_size, _index, _offset };
}
