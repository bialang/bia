#ifndef BIA_MEMBER_FUNCTION_CONTEXT_HPP_
#define BIA_MEMBER_FUNCTION_CONTEXT_HPP_

#include <bia/internal/type/function.hpp>
#include <bia/memory/frame.hpp>
#include <bia/util/algorithm.hpp>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>

namespace bia {
namespace member {
namespace function {

typedef internal::type::Dynamic_function_signature Signature;

/// Provides access for a dynamic function to access the parameters and the return value through this class.
class Context
{
public:
	Context(const Signature& signature, memory::Frame<true>& frame) : _signature{ signature }, _frame{ frame }
	{}

	/// Sets the return value for the function.
	template<typename Type>
	void set_return(Type&& value)
	{
		internal::type::Definition<typename std::decay<Type>::type> definition{};
		if (!_signature.return_definition->is_assignable(&definition)) {
			BIA_ASSERT(false);
		}
		_frame.store(0, std::forward<Type>(value));
		_return_set = true;
	}
	bool return_is_set() const noexcept
	{
		return _return_set;
	}
	/// Retrieves the argument at the specified index.
	template<typename Type>
	Type get_argument(std::size_t index)
	{
		if (index >= _signature.argument_definitions.size()) {
			BIA_ASSERT(false);
		}
		internal::type::Definition<typename std::decay<Type>::type> definition{};
		if (!definition.is_assignable(_signature.argument_definitions[index].definition)) {
			BIA_ASSERT(false);
		}
		std::int32_t offset = util::aligned(sizeof(memory::gc::GC_able<void*>), alignof(std::max_align_t));
		for (std::size_t i = 0; i < index; ++i) {
			offset +=
			  util::aligned(_signature.argument_definitions[i].definition->size(), alignof(std::max_align_t));
		}
		return _frame.load<Type>(offset);
	}

private:
	Signature _signature;
	memory::Frame<true>& _frame;
	bool _return_set = false;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
