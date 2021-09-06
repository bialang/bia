#ifndef BIA_CBIA_STRUCTS_HPP_
#define BIA_CBIA_STRUCTS_HPP_

#include <bia/member/function/context.hpp>
#include <bia/thread/lock/mutex.hpp>
#include <cstddef>

namespace bia {
namespace cbia {

struct Signature
{
	thread::lock::Mutex mutex;
	std::size_t use_count;
	// member::function::Signature signature;
};

} // namespace cbia
} // namespace bia

#endif
