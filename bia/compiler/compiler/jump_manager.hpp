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

	/** the jump type */
	enum class type
	{
		unconditional,
		if_true,
		if_false
	};

	/** the jump destination */
	enum class destination
	{
		end,
		next,
		start
	};

	jump_manager(util::not_null<std::ostream*> output) noexcept;
	/**
	 * Marks the current position as a destination for jumps.
	 *
	 * @note may update the offset of previously set jumps
	 *
	 * @param destination the type of the destination
	 */
	void mark(destination destination);
	/**
	 * Writes a jump to a specific destination.
	 *
	 * @param type the type of the jump
	 * @param destination the jump destination
	 */
	void jump(type type, destination destination);

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

	void _correct_jump(const info& info, pos_type cpos);
	void _write_jump(type type, offset_type offset);
};

} // namespace compiler
} // namespace bia

#endif