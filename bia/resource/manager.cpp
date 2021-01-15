#include "manager.hpp"

using namespace bia::resource;

Manager::Manager(util::Not_null<std::shared_ptr<gc::memory::Allocator>> allocator,
                 std::size_t page_size) noexcept
    : _space(allocator, page_size)
{}

Manager::~Manager()
{
	BIA_EXPECTS(!buf_active());
}

Streambuf Manager::start_memory(bool avoid_duplicates)
{
	BIA_EXPECTS(!buf_active());

	_buf_active = true;

	return { this };
}

Manager::state_type Manager::save_state() const
{
	BIA_EXPECTS(!buf_active());

	return _space.size();
}

void Manager::restore_state(state_type old)
{
	_space.truncate(old);
}

bool Manager::buf_active() const noexcept
{
	return _buf_active;
}
