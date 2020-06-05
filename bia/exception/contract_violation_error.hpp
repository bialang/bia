#ifndef BIA_EXCEPTION_CONTRACT_VIOLATION_ERROR_HPP_
#define BIA_EXCEPTION_CONTRACT_VIOLATION_ERROR_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

/**
 * Thrown if a pre- or postcondition has been violated.
*/
class contract_violation_error : public bia_error
{
public:
	using bia_error::bia_error;

	virtual const char* name() const noexcept override
	{
		return "contract_violation_error";
	}
};

} // namespace exception
} // namespace bia

#endif