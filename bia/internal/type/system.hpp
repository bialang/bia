#ifndef BIA_INTERNAL_TYPE_SYSTEM_HPP_
#define BIA_INTERNAL_TYPE_SYSTEM_HPP_

#include "definition.hpp"

#include <bia/memory/allocator.hpp>
#include <bia/memory/std_allocator.hpp>
#include <map>
#include <type_traits>
#include <utility>
#include <vector>

namespace bia {
namespace internal {
namespace type {

class System
{
public:
	typedef unsigned int Code;

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
		const auto ptr = _allocator->construct<Type>(std::forward<Arguments>(arguments)...);
		_types.insert(std::make_pair(ptr, ++_id_counter));
		return ptr;
	}
	~System() noexcept
	{
		for (const auto& i : _types) {
			_allocator->destroy(i.first);
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
	Code _id_counter = 0;
	std::shared_ptr<memory::Allocator> _allocator;
	std::map<Definition*, Code, std::less<Definition*>, memory::Std_allocator<std::pair<Definition*, Code>>>
	  _types;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
