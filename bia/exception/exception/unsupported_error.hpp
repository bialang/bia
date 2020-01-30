#ifndef BIA_EXCEPTION_UNSUPPORTED_ERROR_HPP_
#define BIA_EXCEPTION_UNSUPPORTED_ERROR_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

/**
 * Thrown when an operation is not supported due to the config.
*/
class unsupported_error : public bia_error
{
public:
	using bia_error::bia_error;
};

} // namespace exception
} // namespace bia

#endif