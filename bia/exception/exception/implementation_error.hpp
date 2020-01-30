#ifndef BIA_EXCEPTION_IMPLEMENTATION_ERROR_HPP_
#define BIA_EXCEPTION_IMPLEMENTATION_ERROR_HPP_

#include "bia_error.hpp"

#define BIA_IMPLEMENTATION_ERROR(msg) BIA_THROW(bia::exception::implementation_error, msg)

namespace bia {
namespace exception {

/**
 * Thrown when a case ocurred that should not have happened. This is a bug.
*/
class implementation_error : public bia_error
{
public:
	using bia_error::bia_error;
};

} // namespace exception
} // namespace bia

#endif