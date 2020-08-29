#ifndef BIA_ERROR_CONTRACT_VIOLATION_HPP_
#define BIA_ERROR_CONTRACT_VIOLATION_HPP_

#include "source_location.hpp"

#include <stdexcept>
#include <utility>

namespace bia {
namespace error {

/**
 * Thrown if a pre- or postcondition has been violated.
 */
class contract_violation : public std::logic_error
{
public:
	contract_violation(const char* msg, class source_location source_location)
	    : logic_error(msg), _source_location{ std::move(source_location) }
	{}
	const class source_location& source_location() const noexcept
	{
		return _source_location;
	}

private:
	class source_location _source_location;
};

} // namespace exception
} // namespace bia

#endif
