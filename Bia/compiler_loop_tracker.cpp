#include "compiler_loop_tracker.hpp"

namespace bia
{
namespace compiler
{

void compiler_loop_tracker::close_loop()
{
	_loops.pop_back();
}

void compiler_loop_tracker::open_loop(position_type _start)
{
	_loops.push_back(loop{ _start });
}

void compiler_loop_tracker::add_end_update(position_type _update_position)
{
	_loops.back().end_jump_update.push_back(_update_position);
}

compiler_loop_tracker::position_type compiler_loop_tracker::loop_start() const
{
	return _loops.back().start;
}

size_t compiler_loop_tracker::open_loops() const noexcept
{
	return _loops.size();
}

const std::vector<compiler_loop_tracker::position_type> & compiler_loop_tracker::end_jump_updates() const noexcept
{
	return _loops.back().end_jump_update;
}

}
}