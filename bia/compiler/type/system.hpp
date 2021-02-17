#ifndef BIA_COMPILER_TYPE_SYSTEM_HPP_
#define BIA_COMPILER_TYPE_SYSTEM_HPP_

#include "definition.hpp"

#include <bia/memory/allocator.hpp>
#include <bia/memory/std_allocator.hpp>
#include <bia/util/finally.hpp>
#include <type_traits>
#include <utility>
#include <vector>

namespace bia {
namespace compiler {
namespace type {

class System
{
public:
	System(util::Not_null<std::shared_ptr<memory::Allocator>> allocator)
	    : _allocator{ allocator.get() }, _types{ allocator }
	{}
	System(const System& copy) = delete;
	System(System&& move) noexcept : _allocator{ move._allocator }, _types{ std::move(move._types) }
	{
		std::swap(_id_counter, move._id_counter);
	}
	template<typename Type, typename... Arguments>
	typename std::enable_if<std::is_base_of<Definition, Type>::value, Type*>::type
	  create_type(Arguments&&... arguments)
	{
		const auto ptr    = _allocator->construct<Type>(_id_counter + 1, std::forward<Arguments>(arguments)...);
		auto final_action = util::finallay([&] { _allocator->destroy(ptr); });
		_types.push_back(ptr);
		final_action.cancel();
		++_id_counter;
		return ptr;
	}
	~System() noexcept
	{
		for (const auto ptr : _types) {
			_allocator->destroy(ptr);
		}
	}
	System& operator=(const System& copy) = delete;
	/// Move operator.
	System& operator=(System&& move) noexcept
	{
		this->~System();
		new (this) System{ std::move(move) };
		return *this;
	}

private:
	unsigned int _id_counter = 0;
	std::shared_ptr<memory::Allocator> _allocator;
	std::vector<Definition*, memory::Std_allocator<Definition*>> _types;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
