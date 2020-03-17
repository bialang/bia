#include "tokenizer/resource/manager.hpps"

namespace bia {
namespace tokenizer {
namespace resource {

manager::manager(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator,
                 std::size_t page_size) noexcept
    : _pages(gc::std_memory_allocator<util::byte*>(allocator)), _allocator(std::move(allocator.get()))
{
	// allocate first page
	_page_size = page_size;
}

manager::~manager()
{
	for (auto& page : _pages) {
		_allocator->deallocate(page);
	}
}

output_streambuf manager::start_memory(bool avoid_duplicates)
{
	BIA_EXPECTS(!buf_active());

	_buf_active = true;

	return { this };
}

state manager::save_state() const
{
	BIA_EXPECTS(!buf_active());

	return _state;
}

void manager::restore_state(const state& old)
{
	BIA_EXPECTS(!_state.older(old));

	_state = old;
}

bool manager::buf_active() const noexcept
{
	return _buf_active;
}

std::pair<util::byte*, util::byte*> manager::_next_page()
{
	// current page can still store
	if (!_pages.empty() && _state._cursor + 8 <= _pages[_state._page_index - 1]) {
		return { _state._cursor, _pages[_state._page_index - 1] + _page_size };
	}

	// no more pages available: allocate new page
	if (_state._page_index + 1 >= _pages.size()) {
		_pages.push_back(static_cast<util::byte*>(_allocator->checked_allocate(_page_size).get()));
	}

	// return next page
	_state._cursor = _pages[_state._page_index++];

	return { _state._cursor, _state._cursor + _page_size };
}

} // namespace resource
} // namespace tokenizer
} // namespace bia