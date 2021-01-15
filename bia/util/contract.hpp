#ifndef BIA_UTIL_CONTRACT_HPP_
#define BIA_UTIL_CONTRACT_HPP_

#include "config.hpp"

#if BIA_UTIL_CONTRACT_BEHAVIOR_THROW
#	include <bia/error/contract_violation.hpp>

#	define BIA_EXPECTS(cond)                                                                                \
		if (!(cond))                                                                                         \
		throw bia::error::Contract_violation("precondition ( " #cond " ) was violated",                      \
		                                     BIA_CURRENT_SOURCE_LOCATION)
#	define BIA_ENSURES(cond)                                                                                \
		if (!(cond))                                                                                         \
		throw bia::error::Contract_violation("postcondition ( " #cond " ) was violated",                     \
		                                     BIA_CURRENT_SOURCE_LOCATION)
#elif BIA_UTIL_CONTRACT_BEHAVIOR_ABORT
#	include <cstdlib>

#	define BIA_EXPECTS(cond)                                                                                \
		if (!(cond))                                                                                         \
		std::abort()
#	define BIA_ENSURES(cond)                                                                                \
		if (!(cond))                                                                                         \
		std::abort()
#else
#	define BIA_EXPECTS(cond) ((void) 0)
#	define BIA_ENSURES(cond) ((void) 0)
#endif

#endif
