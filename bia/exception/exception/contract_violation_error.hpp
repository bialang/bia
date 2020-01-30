#ifndef BIA_EXCEPTION_CONTRACT_VIOLATION_ERROR_HPP_
#define BIA_EXCEPTION_CONTRACT_VIOLATION_ERROR_HPP_

#include "error.hpp"

namespace bia {
namespace exception {

class contract_violation_error : public error
{
public:
	using error::error;
};

} // namespace exception
} // namespace bia

#endif