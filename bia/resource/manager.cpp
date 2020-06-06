#include "manager.hpp"

using namespace bia::resource;

manager::manager(util::not_null<std::shared_ptr<gc::memory::allocator>> allocator,
                 std::size_t page_size) noexcept
    : _space(allocator, page_size)
{}

manager::~manager()
{
	BIA_EXPECTS(!buf_active());
}

streambuf manager::start_memory(bool avoid_duplicates)
{
	BIA_EXPECTS(!buf_active());

	_buf_active = true;

	return { this };
}

manager::state_type manager::save_state() const
{
	BIA_EXPECTS(!buf_active());

	return _space.size();
}

void manager::restore_state(state_type old)
{
	_space.truncate(old);
}

bool manager::buf_active() const noexcept
{
	return _buf_active;
}
