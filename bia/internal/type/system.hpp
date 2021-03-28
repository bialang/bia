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
#include <vector>

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
	template<typename... Types>
	std::vector<const type::Definition*>
	  definitions_of(util::type_traits::type_container<Types...> types = {}) const
	{
		std::vector<const type::Definition*> definitions;
		definitions.reserve(sizeof...(Types));
		_definitions_of(definitions, types);
		return definitions;
	}
	const Definition* definition_of(const std::type_info& type) const;
	template<typename Type, typename... Arguments>
	typename std::enable_if<std::is_base_of<Definition, Type>::value, const Type*>::type
	  get_or_create(Arguments&&... arguments)
	{
		Type type{ std::forward<Arguments>(arguments)... };
		const auto it = _type_index.find(&type);
		if (it != _type_index.end()) {
			return static_cast<const Type*>(it->first);
		}
		// create new
		const auto ptr = _allocator->construct<Type>(std::move(type));
		_type_index.insert(std::make_pair(ptr, ++_id_counter));
		return ptr;
	}
	template<typename Type>
	void link(util::Not_null<const Definition*> definition)
	{
		static_assert(alignof(Type) <= sizeof(std::max_align_t), "over-aligned types are not supported");
		_real_types[{ typeid(Type) }] = definition;
	}
	System& operator=(const System& copy) = delete;
	/// Move operator.
	System& operator=(System&& move) noexcept;

private:
	struct Comparator
	{
		bool operator()(const Definition* left, const Definition* right) const
		{
			return left->compare(right) < 0;
		}
	};

	Code _id_counter = 0;
	/// Memory allocator for the dynamically created types.
	std::shared_ptr<memory::Allocator> _allocator;
	/// Index of all known types.
	std::map<const Definition*, Code, Comparator, memory::Std_allocator<std::pair<const Definition*, Code>>>
	  _type_index;
	/// Mappings of real C++ types to dynamic types. The definition must be in the type index.
	std::map<std::type_index, const Definition*> _real_types;

	static void _definitions_of(std::vector<const type::Definition*>& output,
	                            util::type_traits::type_container<> = {}) noexcept
	{}
	template<typename Type, typename... Others>
	void _definitions_of(std::vector<const type::Definition*>& output,
	                     util::type_traits::type_container<Type, Others...> = {}) const
	{
		output.push_back(definition_of(typeid(Type)));
		_definitions_of(output, util::type_traits::type_container<Others...>{});
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
