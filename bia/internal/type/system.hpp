#ifndef BIA_INTERNAL_TYPE_SYSTEM_HPP_
#define BIA_INTERNAL_TYPE_SYSTEM_HPP_

#include "definition.hpp"

#include <bia/memory/allocator.hpp>
#include <bia/memory/std_allocator.hpp>
#include <bia/util/type_traits/type_select.hpp>
#include <cstddef>
#include <map>
#include <set>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace bia {
namespace internal {
namespace type {

/// Stores and manages all type definitions introduced to it. Additionally real C++ types can be linked with
/// type definitions.
class System
{
public:
	System(util::Not_null<std::shared_ptr<memory::Allocator>> allocator)
	    : _allocator{ allocator.get() }, _type_index{ allocator }, _real_types{ allocator }
	{}
	System(const System& copy)     = delete;
	System(System&& move) noexcept = default;
	~System() noexcept
	{
		for (const auto& definition : _type_index) {
			_allocator->destroy(const_cast<type::Definition_base*>(definition));
		}
	}
	template<typename Type>
	const Definition_base* definition_of()
	{
		using T = typename std::decay<Type>::type;
		Definition<T> type{};
		const auto it = _type_index.find(&type);
		if (it != _type_index.end()) {
			return *it;
		}
		// create new
		const auto ptr = _allocator->construct<Definition<T>>();
		_type_index.insert(ptr);
		return ptr;
	}
	System& operator=(const System& copy) = delete;
	/// Move operator.
	System& operator=(System&& move) noexcept = default;

private:
	/// Memory allocator for the dynamically created types.
	std::shared_ptr<memory::Allocator> _allocator;
	/// Index of all known types.
	std::set<const Definition_base*, std::less<const Definition_base*>,
	         memory::Std_allocator<const Definition_base*>>
	  _type_index;
	/// Mappings of real C++ types to dynamic types. The definition must be in the type index.
	std::map<std::type_index, const Definition_base*, std::less<std::type_index>,
	         memory::Std_allocator<std::pair<std::type_index, const Definition_base*>>>
	  _real_types;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
