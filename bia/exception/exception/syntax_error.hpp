#ifndef BIA_EXCEPTION_SYNTAX_ERROR_HPP_
#define BIA_EXCEPTION_SYNTAX_ERROR_HPP_

#include "bia_error.hpp"

#include <istream>

namespace bia {
namespace exception {

struct syntax_details
{
	/** whether these error details are valid */
	bool valid;
	/** the position in the stream where the error occurred */
	std::istream::pos_type position;
	/** a static error message */
	const char* message;

	syntax_details() noexcept
	{
		valid    = false;
		position = -1;
		message  = nullptr;
	}
	syntax_details(std::istream::pos_type position, const char* message) noexcept
	{
		valid          = true;
		this->position = position;
		this->message  = message;
	}
	operator bool() const noexcept
	{
		return valid;
	}
};

class syntax_error : public bia_error
{
public:
	syntax_error(const char* message, syntax_details details, const char* filename, int line)
	    : bia_error(message, filename, line), _details(std::move(details))
	{}
	const syntax_details& details() const noexcept
	{
		return _details;
	}

private:
	syntax_details _details;
};

} // namespace exception
} // namespace bia

#endif