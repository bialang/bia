#ifndef BIA_EXCEPTION_BOUNDS_ERROR_
#define BIA_EXCEPTION_BOUNDS_ERROR_

#include "bia_error.hpp"

namespace bia {
namespace exception {

/**
 * Thrown when an index is out of bounds.
 */
class bounds_error : public bia_error
{
public:
	using bia_error::bia_error;

	virtual const char* name() const noexcept override
	{
		return "bounds_error";
	}
};

} // namespace exception
} // namespace bia

#endif