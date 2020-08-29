#ifndef BIA_ERROR_EXCEPTION_HPP_
#define BIA_ERROR_EXCEPTION_HPP_

#include "code.hpp"
#include "source_location.hpp"

#include <stdexcept>
#include <system_error>
#include <utility>

#define BIA_THROW(ec) throw bia::error::exception(ec, BIA_CURRENT_SOURCE_LOCATION)

namespace bia {
namespace error {

class exception : public std::runtime_error
{
public:
	exception(std::error_code ec, class source_location source_location)
	    : runtime_error(ec.message()), _ec(std::move(ec)), _source_location{ std::move(source_location) }
	{}
	const std::error_code& error() const noexcept
	{
		return _ec;
	}
	const class source_location& source_location() const noexcept
	{
		return _source_location;
	}

private:
	std::error_code _ec;
	class source_location _source_location;
};

} // namespace error
} // namespace bia

#endif
