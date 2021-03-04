#ifndef BIA_BVM_RESOURCE_OPERATIONS_HPP_
#define BIA_BVM_RESOURCE_OPERATIONS_HPP_

#include "instruction_pointer.hpp"
#include "operations.hpp"

#include <bia/memory/gc/types.hpp>
#include <bia/memory/frame.hpp>
#include <cstdint>
#include <cstring>
#include <regex>
#include <type_traits>

namespace bia {
namespace bvm {

template<typename Operation>
inline bool resource_operation_test(bvm::Operation op, Instruction_pointer& ip, memory::Frame& frame)
{
	const auto arg0 = ip.read<std::int32_t>();
	const auto arg1 = ip.read<std::int32_t>();
	switch (op.variation) {
	case 0:
		return Operation{}(frame.load<memory::gc::GC_able<memory::gc::String*>>(arg0),
		                   frame.load<memory::gc::GC_able<memory::gc::String*>>(arg1));
	case 1:
		return Operation{}(frame.load<memory::gc::GC_able<memory::gc::Regex*>>(arg0),
		                   frame.load<memory::gc::GC_able<memory::gc::String*>>(arg1));
	}
	// TODO
	BIA_ASSERT(false);
}

} // namespace bvm
} // namespace bia

#endif
