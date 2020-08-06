#ifndef BIA_EXCEPTION_INVALID_CODE_POINT_HPP_
#define BIA_EXCEPTION_INVALID_CODE_POINT_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class invalid_code_point : public bia_error
{
public:
	using bia_error::bia_error;
	
	const char* name() const noexcept override
	{
		return "invalid_code_point";
	}
};

} // namespace exception
} // namespace bia

#endif
