#ifndef BIA_EXCEPTION_BOUNDS_ERROR_
#define BIA_EXCEPTION_BOUNDS_ERROR_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class bounds_error : public bia_error
{
public:
	using bia_error::bia_error;
};

} // namespace exception
} // namespace bia

#endif