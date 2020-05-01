#ifndef BIA_EXCEPTION_OPCODE_ERROR_
#define BIA_EXCEPTION_OPCODE_ERROR_

#include "bia_error.hpp"

namespace bia {
namespace exception {

/**
 * Thrown when an index is out of bounds.
 */
class opcode : public bia_error
{
public:
	using bia_error::bia_error;

	virtual const char* name() const noexcept override
	{
		return "opcode";
	}
};

} // namespace exception
} // namespace bia

#endif