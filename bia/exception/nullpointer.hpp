#ifndef BIA_EXCEPTION_NULLPOINTER_HPP_
#define BIA_EXCEPTION_NULLPOINTER_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class nullpointer : public bia_error
{
public:
	using bia_error::bia_error;
	
	const char* name() const noexcept override
	{
		return "nullpointer";
	}
};

} // namespace exception
} // namespace bia

#endif