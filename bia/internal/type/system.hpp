#ifndef BIA_INTERNAL_TYPE_SYSTEM_HPP_
#define BIA_INTERNAL_TYPE_SYSTEM_HPP_

#include "definition.hpp"

#include <bia/memory/allocator.hpp>
#include <bia/memory/std_allocator.hpp>
#include <bia/util/type_traits/type_select.hpp>
#include <cstddef>
#include <map>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace bia {
namespace internal {
namespace type {

/// Stores and manages all types that were declared during compilation or by the user. The types are not
/// required for the runtime, only for compilation.
class System
{
public:
	typedef unsigned int Code;

	System(util::Not_null<std::shared_ptr<memory::Allocator>> allocator);
	System(const System& copy) = delete;
	System(System&& move) noexcept;
	~System() noexcept;
	template<typename Type>
	const Definition_base* definition_of()
	{
		using T = typename std::decay<Type>::type;
		Definition<T> type{};
		const auto it = _type_index.find(&type);
		if (it != _type_index.end()) {
			return it->first;
		}
		// create new
		const auto ptr = _allocator->construct<Definition<T>>();
		_type_index.insert(std::make_pair(ptr, ++_id_counter));
		return ptr;
	}
	System& operator=(const System& copy) = delete;
	/// Move operator.
	System& operator=(System&& move) noexcept;

private:
	struct Comparator
	{
		bool operator()(const Definition_base* left, const Definition_base* right) const
		{
			return left->compare(right) < 0;
		}
	};

	Code _id_counter = 0;
	/// Memory allocator for the dynamically created types.
	std::shared_ptr<memory::Allocator> _allocator;
	/// Index of all known types.
	std::map<const Definition_base*, Code, Comparator,
	         memory::Std_allocator<std::pair<const Definition_base*, Code>>>
	  _type_index;
	/// Mappings of real C++ types to dynamic types. The definition must be in the type index.
	std::map<std::type_index, const Definition_base*> _real_types;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
