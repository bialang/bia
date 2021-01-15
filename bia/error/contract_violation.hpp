#ifndef BIA_ERROR_CONTRACT_VIOLATION_HPP_
#define BIA_ERROR_CONTRACT_VIOLATION_HPP_

#include "source_location.hpp"

#include <stdexcept>
#include <utility>

namespace bia {
namespace error {

/// Thrown if a pre- or postcondition has been violated.
class Contract_violation : public std::logic_error
{
public:
	Contract_violation(const char* msg, class Source_location source_location)
	    : logic_error{ msg }, _source_location{ std::move(source_location) }
	{}
	const class Source_location& source_location() const noexcept
	{
		return _source_location;
	}

private:
	class Source_location _source_location;
};

} // namespace error
} // namespace bia

#endif
