#include "tokenizer/resource/manager.hpp"

namespace bia {
namespace tokenizer {
namespace resource {

manager::manager(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator,
                 std::size_t page_size) noexcept
    : _pages(std::make_shared<memory::page_container_type>(
          gc::std_memory_allocator<util::byte*>(allocator.get()))),
      _allocator(std::move(allocator.get()))
{
	_page_size = page_size;
}

manager::~manager()
{
	for (auto& page : *_pages) {
		_allocator->deallocate(page);
	}
}

memory::streambuf manager::start_memory(bool avoid_duplicates)
{
	BIA_EXPECTS(!buf_active());

	_buf_active = true;

	return { this };
}

memory::memory manager::stop_memory(memory::streambuf& buf)
{
	BIA_EXPECTS(buf_active());

	_buf_active = false;

	// finalize size
	buf.finish();

	return {};
	// return { buf._begin };
}

void manager::discard_memory()
{
	BIA_EXPECTS(buf_active());

	_buf_active = false;
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

std::pair<size*, util::byte*> manager::_next_size()
{
	// current page can hold more
	if (!_pages->empty() && _state.cursor + 8 <= (*_pages)[_state.page_index] + _page_size) {
		} // allocate new page
	else if (_pages->size() <= _state.page_index) {
		_pages->push_back(static_cast<util::byte*>(_allocator->checked_allocate(_page_size).get()));
	}

	_state.cursor = (*_pages)[_state.page_index];
	++_state.page_index;

	return { new (_state.cursor) size{}, (*_pages)[_state.page_index - 1] + _page_size };
}

} // namespace resource
} // namespace tokenizer
} // namespace bia