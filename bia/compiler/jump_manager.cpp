#include "jump_manager.hpp"

using namespace bia::compiler;

jump_manager::jump_manager(util::not_null<std::ostream*> output) noexcept : _output(*output)
{}

void jump_manager::mark(destination destination)
{
	const auto cpos = _output.tellp();

	switch (destination) {
	case destination::next: {
		BIA_EXPECTS(_last.pos != pos_type{ -1 });

		_correct_jump(_last, cpos);

		_last = { { -1 } };

		break;
	}
	case destination::end: {
		for (const auto& i : _end_jumps) {
			_correct_jump(i, cpos);
		}

		break;
	}
	case destination::start: {
		_start = cpos;

		return;
	}
	}

	_output.seekp(cpos);
}

void jump_manager::clear(destination destination)
{
	switch (destination) {
	case destination::next: _last = { -1 }; break;
	case destination::end: _end_jumps.clear(); break;
	case destination::start: _start = { -1 }; break;
	}
}

void jump_manager::jump(type type, destination destination)
{
	const pos_type cpos = _output.tellp();

	switch (destination) {
	case destination::next: {
		BIA_EXPECTS(_last.pos == pos_type{ -1 });

		_last = { cpos, type };

		break;
	}
	case destination::end: {
		_end_jumps.push_back({ cpos, type });

		break;
	}
	case destination::start: {
		BIA_EXPECTS(_start != pos_type{ -1 });

		_write_jump(type, _start - cpos - _jump_size);

		return;
	}
	}

	_write_jump(type, 0);
}

void jump_manager::_correct_jump(const info& info, pos_type cpos)
{
	_output.seekp(info.pos);
	_write_jump(info.type, cpos - info.pos - _jump_size);
}

void jump_manager::_write_jump(type type, offset_type offset)
{
	switch (type) {
	case type::unconditional:
		bytecode::writer::instruction(_output).write<false, bytecode::oc_jump>(offset);

		break;
	case type::if_true:
		bytecode::writer::instruction(_output).write<false, bytecode::oc_jump_true>(offset);

		break;
	case type::if_false:
		bytecode::writer::instruction(_output).write<false, bytecode::oc_jump_false>(offset);

		break;
	}
}
