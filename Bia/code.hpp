#pragma once


namespace bia
{
namespace machine
{

class code
{
public:
	virtual ~code() noexcept = default;
	virtual void execute() = 0;
	virtual void clear() = 0;
	virtual void disassemble() = 0;
	/**
	 * Checks wheter the code is executable.
	 *
	 * @remarks This function does not check if the machine code itself is valid.
	 *
	 * @since 3.42.93.562
	 * @date 14-Dec-2017
	 *
	 * @return true if the code can be executed, otherwise false.
	 */
	virtual bool is_executable() const noexcept = 0;
};

}
}