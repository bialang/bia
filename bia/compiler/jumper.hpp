#ifndef BIA_COMPILER_JUMPER_HPP_
#define BIA_COMPILER_JUMPER_HPP_

#include <bia/bytecode/instructor.hpp>
#include <ostream>
#include <vector>

namespace bia {
namespace compiler {

class Jumper
{
public:
	typedef std::ostream::pos_type Position;
	typedef std::int32_t Offset;

	/// The jump condition type.
	enum class Type
	{
		unconditional,
		if_true,
		if_false
	};

	/// The jump destination.
	enum class Destination
	{
		end,
		next,
		start
	};

	Jumper(bytecode::Instructor& instructor) noexcept;
	/**
	 * Marks the current position as a destination for jumps.
	 *
	 * @note may update the offset of previously set jumps
	 *
	 * @param destination the type of the destination
	 */
	void mark(Destination destination);
	/**
	 * Clears the stored jumps.
	 *
	 * @warning this does not delete the jumps, but only deregistering them from updating when
	 * jump_manager::mark() is called
	 *
	 * @param destination the type of the destination
	 */
	void clear(Destination destination);
	/**
	 * Writes a jump to a specific destination.
	 *
	 * @param type the type of the jump
	 * @param destination the jump destination
	 */
	void jump(Type type, Destination destination);

private:
	struct Info
	{
		Position pos;
		Type type;
	};

	constexpr static auto _jump_size = sizeof(bytecode::Op_code) + sizeof(Offset);

	bytecode::Instructor& _instructor;
	Position _start{ -1 };
	Info _last{ { -1 } };
	std::vector<Info> _end_jumps;

	void _correct_jump(const Info& info, Position cpos);
	void _write_jump(Type type, Offset offset);
};

} // namespace compiler
} // namespace bia

#endif
