#include "jumper.hpp"

#include <bia/util/gsl.hpp>

using namespace bia::compiler;

Jumper::Jumper(bytecode::Instructor& instructor) noexcept : _instructor{ instructor }
{}

void Jumper::mark(Destination destination)
{
	const auto cpos = _instructor.output().tellp();
	switch (destination) {
	case Destination::next: {
		BIA_EXPECTS(_last.pos != Position{ -1 });
		_correct_jump(_last, cpos);
		_last = { { -1 } };
		break;
	}
	case Destination::end: {
		for (const auto& i : _end_jumps) {
			_correct_jump(i, cpos);
		}
		break;
	}
	case Destination::start: _start = cpos; return;
	default: BIA_THROW(error::Code::bad_switch_value);
	}
	_instructor.output().seekp(cpos);
}

void Jumper::clear(Destination destination)
{
	switch (destination) {
	case Destination::next: _last = { -1 }; break;
	case Destination::end: _end_jumps.clear(); break;
	case Destination::start: _start = { -1 }; break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}
}

void Jumper::jump(Type type, Destination destination)
{
	const Position cpos = _instructor.output().tellp();
	switch (destination) {
	case Destination::next: {
		BIA_EXPECTS(_last.pos == Position{ -1 });
		_last = { cpos, type };
		break;
	}
	case Destination::end: _end_jumps.push_back({ cpos, type }); break;
	case Destination::start: {
		BIA_EXPECTS(_start != Position{ -1 });
		_write_jump(type, _start - cpos - _jump_size);
		return;
	}
	default: BIA_THROW(error::Code::bad_switch_value);
	}
	_write_jump(type, 0);
}

void Jumper::_correct_jump(const Info& info, Position cpos)
{
	_instructor.output().seekp(info.pos);
	_write_jump(info.type, cpos - info.pos - _jump_size);
}

void Jumper::_write_jump(Type type, Offset offset)
{
	switch (type) {
	case Type::unconditional: _instructor.write<bytecode::Op_code::jump>(offset); break;
	case Type::if_true: _instructor.write<bytecode::Op_code::jump_true>(offset); break;
	case Type::if_false: _instructor.write<bytecode::Op_code::jump_false>(offset); break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}
}
