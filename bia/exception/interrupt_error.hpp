#ifndef BIA_EXCEPTION_INTERRUPT_ERROR_HPP_
#define BIA_EXCEPTION_INTERRUPT_ERROR_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

/**
 * Thrown when the current thread was interrupted during or before some special blocking operations.
 */
class interrupt_error : public bia_error
{
public:
	using bia_error::bia_error;

	virtual const char* name() const noexcept override
	{
		return "interrupt_error";
	}
};

} // namespace exception
} // namespace bia

#endif