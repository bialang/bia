#ifndef BIA_INTERNAL_NAMESPACE_HPP_
#define BIA_INTERNAL_NAMESPACE_HPP_

#include "string_key.hpp"
#include "type/bool.hpp"
#include "type/floating_point.hpp"
#include "type/function.hpp"
#include "type/integer.hpp"
#include "type/regex.hpp"
#include "type/string.hpp"
#include "type/void.hpp"

#include <bia/internal/type/definition.hpp>
#include <bia/internal/type/system.hpp>
#include <bia/member/function/creator.hpp>
#include <bia/memory/frame.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/optional.hpp>
#include <bia/util/type_traits/invokable_info.hpp>
#include <bia/util/type_traits/type_select.hpp>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace bia {
namespace internal {

struct Symbol
{
	std::size_t offset;
	const type::Definition* definition;
};

class Namespace
{
public:
	Namespace(internal::type::System& type_system, memory::gc::GC& gc) noexcept
	    : _type_system{ type_system }, _gc{ gc },
	      _global_space{ static_cast<util::Byte*>(gc.allocator()->allocate(1024)), 1024 }, _global_frame{
		      _global_space, _gc, 0
	      }
	{
		using namespace internal::type;

		const Definition* def = nullptr;
		_global_index.insert(std::make_pair(
		  util::from_cstring("int"),
		  static_cast<const Definition*>(_type_system.get_or_create<Integer>(Integer::Size::i32, true))));
		_global_index.insert(std::make_pair(
		  util::from_cstring("uint"),
		  static_cast<const Definition*>(_type_system.get_or_create<Integer>(Integer::Size::u32, true))));

		_global_index.insert(std::make_pair(util::from_cstring("void"),
		                                    static_cast<const Definition*>(_type_system.get_or_create<Void>())));

		_global_index.insert(
		  std::make_pair(util::from_cstring("bool"), def = _type_system.get_or_create<Bool>()));
		_type_system.link<bool>(def);

		_global_index.insert(std::make_pair(
		  util::from_cstring("int32"),
		  static_cast<const Definition*>(_type_system.get_or_create<Integer>(Integer::Size::i32, false))));
		_global_index.insert(std::make_pair(
		  util::from_cstring("uint64"),
		  static_cast<const Definition*>(_type_system.get_or_create<Integer>(Integer::Size::u64, false))));

		_global_index.insert(std::make_pair(
		  util::from_cstring("float32"),
		  static_cast<const Definition*>(_type_system.get_or_create<Floating_point>(Floating_point::Size::f32))));

		_global_index.insert(std::make_pair(
		  util::from_cstring("string"), static_cast<const Definition*>(_type_system.get_or_create<String>())));
		_global_index.insert(std::make_pair(util::from_cstring("regex"),
		                                    static_cast<const Definition*>(_type_system.get_or_create<Regex>())));
	}
	template<typename Invokeable>
	void put_invokable(String_key name, Invokeable&& invokable)
	{
		static_assert(util::type_traits::Invokable_info<Invokeable>::is_invokable,
		              "Invokeable must be a invokable");
		if (_global_index.find(name) != _global_index.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}

		// get types of signature
		const auto return_type =
		  _type_system.definition_of(typeid(typename util::type_traits::Invokable_info<Invokeable>::Return));
		auto argument_definitions =
		  _type_system.definitions_of(util::type_traits::Invokable_info<Invokeable>::arguments);
		BIA_ASSERT(argument_definitions.size() == util::type_traits::Invokable_info<Invokeable>::argument_count);
		std::vector<type::Argument> arguments;
		arguments.reserve(argument_definitions.size());
		for (const auto definition : argument_definitions) {
			arguments.push_back({ definition });
		}

		// TODO alignment of types
		// TODO protect ptr from GC, because it cannot be collected in global namespace
		const auto ptr = member::function::create(_gc, std::forward<Invokeable>(invokable));
		_global_frame.store(_offset, ptr);
		auto function_definition = _type_system.get_or_create<type::Function>(return_type, arguments);
		_global_index.insert({ name, Symbol{ _offset, function_definition } });
		_offset += util::aligned(sizeof(ptr), alignof(std::max_align_t));
	}
	memory::Frame<false> globals() const
	{
		return _global_frame;
	}
	util::Variant<Symbol, const type::Definition*> global(const String_key& name) const
	{
		const auto it = _global_index.find(name);
		if (it != _global_index.end()) {
			return it->second;
		}
		return {};
	}

private:
	internal::type::System& _type_system;
	memory::gc::GC& _gc;
	std::size_t _offset = 0;
	util::Span<util::Byte*> _global_space;
	memory::Frame<true> _global_frame;
	/// Maps names to the global symbols relative to the global frame.
	std::map<String_key, util::Variant<Symbol, const type::Definition*>, String_comparator> _global_index;
};

} // namespace internal
} // namespace bia

#endif
