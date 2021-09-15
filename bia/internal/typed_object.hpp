#ifndef BIA_INTERNAL_TYPED_OBJECT_HPP_
#define BIA_INTERNAL_TYPED_OBJECT_HPP_

#include "string_key.hpp"
#include "type/definitions.hpp"
#include "type/system.hpp"

#include <bia/member/function/creator.hpp>
#include <bia/member/function/dynamic.hpp>
#include <bia/member/object.hpp>
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

class Typed_object : public member::Object
{
public:
	Typed_object(internal::type::System& type_system, memory::gc::GC& gc)
	    : Object{ gc, 1024 }, _type_system{ type_system }, _gc{ gc }
	{}
	template<typename Type>
	void put_value(String_key name, Type&& value, bool immutable = true)
	{
		if (_symbols.find(name) != _symbols.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}

		type::Variable variable{};
		variable.offset     = store(std::forward<Type>(value));
		variable.definition = _type_system.definition_of<Type>();
		variable.flags      = immutable ? 0 : type::Variable::flag_mutable;
		_symbols.insert({ name, variable });
	}
	template<typename Invokeable>
	void put_invokable(String_key name, Invokeable&& invokable, bool immutable = true)
	{
		static_assert(util::type_traits::Invokable_info<Invokeable>::is_invokable,
		              "Invokeable must be a invokable");
		if (_symbols.find(name) != _symbols.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}

		// TODO alignment of types
		// TODO protect ptr from GC, because it cannot be collected in global namespace
		type::Variable variable{};
		variable.offset = store(member::function::create(_gc, std::forward<Invokeable>(invokable)));
		variable.definition =
		  _type_system.definition_of<typename util::type_traits::Invokable_info<Invokeable>::Signature>();
		variable.flags = immutable ? 0 : type::Variable::flag_mutable;
		_symbols.insert({ name, variable });
	}
	void put_invokable(String_key name, member::function::Dynamic_invokable invokable,
	                   member::function::Signature signature, bool immutable = true)
	{
		if (_symbols.find(name) != _symbols.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}

		type::Variable variable{};
		variable.offset     = store(_gc.create<member::function::Dynamic>(signature, std::move(invokable)));
		variable.definition = _type_system.register_definition(
		  internal::type::Definition<internal::type::Dynamic_function>{ signature });
		variable.flags = immutable ? 0 : type::Variable::flag_mutable;
		_symbols.insert({ name, variable });
	}
	void put_object(String_key name, Typed_object object, bool immutable = true)
	{
		if (_symbols.find(name) != _symbols.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}

		type::Variable variable{};
		// TODO optimize used memory
		variable.definition = _type_system.register_definition(
		  internal::type::Definition<internal::type::Dynamic_object>{ std::move(object._symbols) });
		variable.offset = store(_gc.create<member::Object>(std::move(object)));
		variable.flags  = immutable ? 0 : type::Variable::flag_mutable;
		_symbols.insert({ name, variable });
	}
	type::Definition<type::Dynamic_object>::Symbol symbol(const String_key& name) const
	{
		const auto it = _symbols.find(name);
		if (it != _symbols.end()) {
			return it->second;
		}
		return {};
	}
	internal::type::System& type_system() noexcept
	{
		return _type_system;
	}
	memory::gc::GC& gc() noexcept
	{
		return _gc;
	}

protected:
	internal::type::System& _type_system;
	memory::gc::GC& _gc;
	type::Definition<type::Dynamic_object>::Map _symbols;
};

} // namespace internal
} // namespace bia

#endif
