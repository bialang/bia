#ifndef BIA_EXCEPTION_NARROWING_ERROR_
#define BIA_EXCEPTION_NARROWING_ERROR_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class narrowing_error : public bia_error
{
public:
	using bia_error::bia_error;

	virtual const char* name() const noexcept override
	{
		return "narrowing_error";
	}
};

} // namespace exception
} // namespace bia

#endif
