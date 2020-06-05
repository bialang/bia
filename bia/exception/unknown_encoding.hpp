#ifndef BIA_EXCEPTION_UNKNOWN_ENCODING_HPP_
#define BIA_EXCEPTION_UNKNOWN_ENCODING_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class unknown_encoding : public bia_error
{
public:
	using bia_error::bia_error;
	
	const char* name() const noexcept override
	{
		return "unknown_encoding";
	}
};

} // namespace exception
} // namespace bia

#endif