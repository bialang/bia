#ifndef BIA_INTERNAL_TYPE_SYSTEM_HPP_
#define BIA_INTERNAL_TYPE_SYSTEM_HPP_

#include "definition.hpp"

#include <bia/memory/allocator.hpp>
#include <bia/memory/std_allocator.hpp>
#include <map>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <cstddef>
#include <utility>
#include <vector>

namespace bia {
namespace internal {
namespace type {

class System
{
public:
	typedef unsigned int Code;

	System(util::Not_null<std::shared_ptr<memory::Allocator>> allocator);
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
	Definition* defintion_of(const std::type_info& type) const
	{
		const auto it = _real_types.find({ type });
		if (it != _real_types.end()) {
			return it->second;
		}
		return nullptr;
	}
	template<typename Type>
	void link(util::Not_null<Definition*> definition)
	{
		static_assert(alignof(Type) <= sizeof(std::max_align_t), "over-aligned types are not supported");
		_real_types[{ typeid(Type) }] = definition;
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
	std::map<std::type_index, Definition*> _real_types;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
