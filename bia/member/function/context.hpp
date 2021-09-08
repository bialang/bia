#ifndef BIA_MEMBER_FUNCTION_CONTEXT_HPP_
#define BIA_MEMBER_FUNCTION_CONTEXT_HPP_

#include <bia/error/exception.hpp>
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
	{
		// load parameter count
		if (_signature.vararg_definition.has_value()) {
			// subtract the size of the hidden vararg count variable, because it will automatically included
			const std::int32_t offset = _calculate_offset(_signature.argument_definitions.empty()
			                                                ? 0
			                                                : _signature.argument_definitions.size() - 1) -
			                            util::aligned(sizeof(std::ptrdiff_t), alignof(std::max_align_t));
			_vararg_count = _frame.load<std::ptrdiff_t>(offset);
			BIA_ASSERT(_vararg_count >= 0);
		}
	}

	/// Sets the return value for the function.
	template<typename Type>
	void set_return(Type&& value)
	{
		internal::type::Definition<typename std::decay<Type>::type> definition{};
		if (!_signature.return_definition->is_assignable(&definition)) {
			BIA_THROW(error::Code::bad_return_type);
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
		if (index >= _signature.argument_definitions.size() + _vararg_count) {
			BIA_THROW(error::Code::out_of_bounds);
		}
		internal::type::Definition<typename std::decay<Type>::type> definition{};
		if (!definition.is_assignable(index < _signature.argument_definitions.size()
		                                ? _signature.argument_definitions[index].definition
		                                : _signature.vararg_definition->definition)) {
			BIA_ASSERT(false);
		}
		return _frame.load<Type>(_calculate_offset(index));
	}
	std::size_t vararg_argument_count() const noexcept
	{
		return static_cast<std::size_t>(_vararg_count);
	}
	std::size_t size() const noexcept
	{
		return _signature.argument_definitions.size() + vararg_argument_count();
	}

private:
	Signature _signature;
	memory::Frame<true>& _frame;
	std::ptrdiff_t _vararg_count = 0;
	bool _return_set             = false;

	std::int32_t _calculate_offset(std::size_t index) const
	{
		std::int32_t offset = util::aligned(sizeof(memory::gc::GC_able<void*>), alignof(std::max_align_t));
		for (std::size_t i = 0; i < index && i < _signature.argument_definitions.size(); ++i) {
			offset +=
			  util::aligned(_signature.argument_definitions[i].definition->size(), alignof(std::max_align_t));
		}
		if (_signature.vararg_definition.has_value()) {
			offset += util::aligned(sizeof(std::ptrdiff_t), alignof(std::max_align_t));
			for (auto i = _signature.argument_definitions.size(); i < index; ++i) {
				offset += util::aligned(_signature.vararg_definition->definition->size(), alignof(std::max_align_t));
			}
		}
		return offset;
	}
};

} // namespace function
} // namespace member
} // namespace bia

#endif
