#ifndef BIA_COMPILER_JUMP_MANAGER_HPP_
#define BIA_COMPILER_JUMP_MANAGER_HPP_

#include <bytecode/writer/instruction.hpp>
#include <ostream>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace compiler {

class jump_manager
{
public:
	typedef std::ostream::pos_type pos_type;
	typedef std::int32_t offset_type;

	enum class type
	{
		unconditional,
		if_true,
		if_false
	};

	enum class destination
	{
		end,
		next,
		start
	};

	jump_manager(util::not_null<std::ostream*> output) noexcept : _output(*output)
	{}
	void mark(destination destination)
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
	void jump(type type, destination destination)
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

private:
	struct info
	{
		pos_type pos;
		type type;
	};

	constexpr static auto _jump_size = sizeof(bytecode::op_code) + sizeof(offset_type);

	std::ostream& _output;
	pos_type _start{ -1 };
	info _last{ { -1 } };
	std::vector<info> _end_jumps;

	void _correct_jump(const info& info, pos_type cpos)
	{
		_output.seekp(info.pos);
		_write_jump(info.type, cpos - info.pos - _jump_size);
	}
	void _write_jump(type type, offset_type offset)
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
};

} // namespace compiler
} // namespace bia

#endif