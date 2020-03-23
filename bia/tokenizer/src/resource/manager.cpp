#include "tokenizer/resource/manager.hpp"

namespace bia {
namespace tokenizer {
namespace resource {

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

gc::memory::view manager::stop_memory(streambuf& buf)
{
	BIA_EXPECTS(buf_active() && buf.valid());

	auto begin = buf._begin;

	_buf_active = false;

	buf.close();

	return { _space.cursor(begin), _space.cursor() };
}

void manager::discard_memory(streambuf& buf)
{
	BIA_EXPECTS(buf_active() && buf.valid());

	_buf_active = false;

	buf.close();
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

} // namespace resource
} // namespace tokenizer
} // namespace bia