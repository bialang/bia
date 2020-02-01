#ifndef BIA_EXCEPTION_MEMORY_ERROR_HPP_
#define BIA_EXCEPTION_MEMORY_ERROR_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class memory_error : public bia_error
{
public:
	using bia_error::bia_error;

	virtual const char* name() const noexcept override
	{
		return "memory_error";
	}
};

} // namespace exception
} // namespace bia

#endif