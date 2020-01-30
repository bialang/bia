#ifndef BIA_UTIL_CONTRACT_HPP_
#define BIA_UTIL_CONTRACT_HPP_

#include "config.hpp"

#if defined(BIA_UTIL_CONTRACT_BEHAVIOR_THROW)
#	include <exception/contract_violation_error.hpp>
#elif defined(BIA_UTIL_CONTRACT_BEHAVIOR_ABORT)
#	include <cstdlib>
#endif

namespace bia {
namespace util {

class contract
{
public:
	static void expect(bool condition)
	{
#if defined(BIA_UTIL_CONTRACT_BEHAVIOR_THROW)
		if (!condition) {
			throw exception::contract_violation_error("precondition invalid");
		}
#elif defined(BIA_UTIL_CONTRACT_BEHAVIOR_ABORT)
		if (!condition) {
			std::abort();
		}
#endif
	}
	static void ensure(bool condition)
	{
#if defined(BIA_UTIL_CONTRACT_BEHAVIOR_THROW)
		if (!condition) {
			throw exception::contract_violation_error("postcondition invalid");
		}
#elif defined(BIA_UTIL_CONTRACT_BEHAVIOR_ABORT)
		if (!condition) {
			std::abort();
		}
#endif
	}
};

} // namespace util
} // namespace bia

#endif