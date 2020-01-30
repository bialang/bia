#ifndef BIA_EXCEPTION_UNSUPPORTED_ERROR_HPP_
#define BIA_EXCEPTION_UNSUPPORTED_ERROR_HPP_

#include "error.hpp"

namespace bia {
namespace exception {

class unsupported_error : public error
{
public:
	using error::error;
};

} // namespace exception
} // namespace bia

#endif