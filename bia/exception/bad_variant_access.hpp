#ifndef BIA_EXCEPTION_BAD_VARIANT_ACCESS_HPP_
#define BIA_EXCEPTION_BAD_VARIANT_ACCESS_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class bad_variant_access : public bia_error
{
public:
	using bia_error::bia_error;

	const char* name() const noexcept override
	{
		return "bad_variant_access";
	}
};

} // namespace exception
} // namespace bia

#endif