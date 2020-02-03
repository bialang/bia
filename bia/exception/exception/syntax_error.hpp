#ifndef BIA_EXCEPTION_SYNTAX_ERROR_HPP_
#define BIA_EXCEPTION_SYNTAX_ERROR_HPP_

#include "bia_error.hpp"

#include <istream>

namespace bia {
namespace exception {

struct syntax_details
{
	bool valid;
	std::istream::pos_type position = -1;
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