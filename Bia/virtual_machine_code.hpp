#pragma once

#include <cstdint>
#include <vector>

#include "config.hpp"
#include "allocator.hpp"
#include "member.hpp"
#include "share.hpp"
#include "machine_context.hpp"
#include "virtual_machine_schein.hpp"
#include "code.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

class virtual_machine_code : public code
{
public:
	BIA_EXPORT virtual_machine_code(memory::universal_allocation _code, virtual_machine_schein && _schein, bool _take_ownership = false);
	virtual_machine_code(const virtual_machine_code & _copy) = delete;
	BIA_EXPORT virtual_machine_code(virtual_machine_code && _move);
	/**
	 * Destructor.
	 *
	 * @since 3.72.149.810
	 * @date 18-Jan-19
	 *
	 * @throws See clear().
	*/
	BIA_EXPORT ~virtual_machine_code();

	BIA_EXPORT virtual void execute() override;
	BIA_EXPORT virtual void clear() override;
	BIA_EXPORT virtual bool is_executable() const noexcept override;

private:
	/** Contains the instructions for the virtual machine code. */
	memory::allocation<uint8_t> _code;
	/** The machine schein.  */
	virtual_machine_schein _schein;
};

}
}
}