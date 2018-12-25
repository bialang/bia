#pragma once

#include <vector>

#include "output_stream.hpp"


namespace bia
{
namespace compiler
{

class compiler_loop_tracker
{
public:
	typedef stream::output_stream::cursor_type position_type;

	void close_loop();
	void open_loop(position_type _start);
	void add_end_update(position_type _update_position);
	position_type loop_start() const;
	size_t open_loops() const noexcept;
	const std::vector<position_type> & end_jump_updates() const noexcept;
private:
	struct loop
	{
		position_type start;
		std::vector<position_type> end_jump_update;
	};

	std::vector<loop> _loops;
};

}
}