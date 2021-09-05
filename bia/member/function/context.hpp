#ifndef BIA_MEMBER_FUNCTION_CONTEXT_HPP_
#define BIA_MEMBER_FUNCTION_CONTEXT_HPP_

#include <bia/memory/frame.hpp>
#include <cstddef>
#include <typeinfo>
#include <utility>
#include <vector>

namespace bia {
namespace member {
namespace function {

/// Describes the function signature of a dynamically created function.
struct Signature
{
	const std::type_info* return_type;
	std::vector<const std::type_info*> arguments;
};

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
		if (typeid(Type) == *_signature.return_type) {
			_frame.store(0, std::forward<Type>(value));
		}
	}
	/// Retrieves the argument at the specified index.
	template<typename Type>
	Type get_argument(std::size_t index)
	{
		if (typeid(Type) == *_signature.arguments.at(index)) {
			
		}
	}

private:
	Signature _signature;
	memory::Frame<true>& _frame;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
