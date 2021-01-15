#ifndef BIA_ERROR_EXCEPTION_HPP_
#define BIA_ERROR_EXCEPTION_HPP_

#include "code.hpp"
#include "source_location.hpp"

#include <stdexcept>
#include <system_error>
#include <utility>

#define BIA_THROW(ec) throw bia::error::Exception(ec, BIA_CURRENT_SOURCE_LOCATION)

namespace bia {
namespace error {

class Exception : public std::runtime_error
{
public:
	Exception(std::error_code ec, class Source_location source_location)
	    : runtime_error{ ec.message() }, _ec{ std::move(ec) }, _source_location{ std::move(source_location) }
	{}
	const std::error_code& code() const noexcept
	{
		return _ec;
	}
	const class Source_location& source_location() const noexcept
	{
		return _source_location;
	}

private:
	std::error_code _ec;
	class Source_location _source_location;
};

} // namespace error
} // namespace bia

#endif
