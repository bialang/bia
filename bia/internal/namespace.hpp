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
#include <bia/member/function/static.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/optional.hpp>
#include <map>
#include <string>
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
	    : _type_system{ type_system }, _gc{ gc }
	{
		static type::String s;
		static type::Integer i{ type::Integer::Size::i32, true };
		static type::Function foo{ &i, { { &s }, { &i } } };
		_global_index.insert({ util::from_cstring("foo"), Symbol{ 0, &foo } });

		const auto ptr = gc.create<member::function::Static<int, std::string, int>>([](std::string i, int j) {
			printf("hello world - '%s' | %d!\n", i.c_str(), j);
			return static_cast<int>(i.length() * j);
		});
		_globals.resize(sizeof(ptr));
		std::memcpy(_globals.data(), &ptr, sizeof(ptr));

		using namespace internal::type;

		_global_index.insert(std::make_pair(
		  util::from_cstring("int"),
		  static_cast<const Definition*>(_type_system.create_type<Integer>(Integer::Size::i32, true))));
		_global_index.insert(std::make_pair(
		  util::from_cstring("uint"),
		  static_cast<const Definition*>(_type_system.create_type<Integer>(Integer::Size::u32, true))));

		_global_index.insert(std::make_pair(util::from_cstring("void"),
		                                    static_cast<const Definition*>(_type_system.create_type<Void>())));

		_global_index.insert(std::make_pair(util::from_cstring("bool"),
		                                    static_cast<const Definition*>(_type_system.create_type<Bool>())));

		_global_index.insert(std::make_pair(
		  util::from_cstring("int32"),
		  static_cast<const Definition*>(_type_system.create_type<Integer>(Integer::Size::i32, false))));

		_global_index.insert(std::make_pair(
		  util::from_cstring("float32"),
		  static_cast<const Definition*>(_type_system.create_type<Floating_point>(Floating_point::Size::f32))));

		_global_index.insert(std::make_pair(util::from_cstring("string"),
		                                    static_cast<const Definition*>(_type_system.create_type<String>())));
		_global_index.insert(std::make_pair(util::from_cstring("regex"),
		                                    static_cast<const Definition*>(_type_system.create_type<Regex>())));
	}
	void put_function(String_key name)
	{
		if (_global_index.find(name) != _global_index.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}
	}
	// util::Span<int*> modules();
	util::Span<const util::Byte*> globals() const
	{
		return {_globals.data(), _globals.size()};
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
	// std::vector<int> _modules;
	std::vector<util::Byte> _globals;
	// std::map<resource::String_key, std::size_t, resource::String_comparator> _module_index;
	std::map<String_key, util::Variant<Symbol, const type::Definition*>, String_comparator> _global_index;
};

} // namespace internal
} // namespace bia

#endif
