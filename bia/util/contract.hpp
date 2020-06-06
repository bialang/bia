#ifndef BIA_UTIL_CONTRACT_HPP_
#define BIA_UTIL_CONTRACT_HPP_

#include "config.hpp"

#if defined(BIA_UTIL_CONTRACT_BEHAVIOR_THROW)
#	include <bia/exception/contract_violation_error.hpp>

#define BIA_EXPECTS(cond) if (!(cond)) BIA_THROW(bia::exception::contract_violation_error, "precondition ( " #cond " ) was violated")
#define BIA_ENSURES(cond) if (!(cond)) BIA_THROW(bia::exception::contract_violation_error, "postcondition ( " #cond " ) was violated")
#elif defined(BIA_UTIL_CONTRACT_BEHAVIOR_ABORT)
#	include <cstdlib>

#define BIA_EXPECTS(cond) if (!(cond)) std::abort()
#define BIA_ENSURES(cond) if (!(cond)) std::abort()
#elif defined(BIA_UTIL_CONTRACT_BEHAVIOR_NOTHING)
#define BIA_EXPECTS(cond) ((void)0)
#define BIA_ENSURES(cond) ((void)0)
#endif

#endif
