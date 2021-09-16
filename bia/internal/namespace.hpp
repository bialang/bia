#ifndef BIA_INTERNAL_NAMESPACE_HPP_
#define BIA_INTERNAL_NAMESPACE_HPP_

#include "string_key.hpp"
#include "type/definitions.hpp"
#include "type/system.hpp"
#include "typed_object.hpp"

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

class Namespace : public Typed_object
{
public:
	Namespace(internal::type::System& type_system, memory::gc::GC& gc) : Typed_object{ type_system, gc }
	{
		// link Bia's data types to definitions
		_symbols.insert(std::make_pair(util::from_cstring("void"), _type_system.definition_of<void>()));
		_symbols.insert(std::make_pair(util::from_cstring("bool"), _type_system.definition_of<bool>()));

		_symbols.insert(std::make_pair(util::from_cstring("byte"), _type_system.definition_of<std::uint8_t>()));
		_symbols.insert(std::make_pair(util::from_cstring("int8"), _type_system.definition_of<std::int8_t>()));
		_symbols.insert(std::make_pair(util::from_cstring("uint8"), _type_system.definition_of<std::uint8_t>()));

		_symbols.insert(std::make_pair(util::from_cstring("int16"), _type_system.definition_of<std::int16_t>()));
		_symbols.insert(
		  std::make_pair(util::from_cstring("uint16"), _type_system.definition_of<std::uint16_t>()));

		_symbols.insert(std::make_pair(util::from_cstring("int32"), _type_system.definition_of<std::int32_t>()));
		_symbols.insert(
		  std::make_pair(util::from_cstring("uint32"), _type_system.definition_of<std::uint32_t>()));

		_symbols.insert(std::make_pair(util::from_cstring("int"), _type_system.definition_of<std::ptrdiff_t>()));
		_symbols.insert(
		  std::make_pair(util::from_cstring("uint"),
		                 _type_system.definition_of<typename std::make_unsigned<std::ptrdiff_t>::type>()));

		_symbols.insert(std::make_pair(util::from_cstring("int64"), _type_system.definition_of<std::int64_t>()));
		_symbols.insert(
		  std::make_pair(util::from_cstring("uint64"), _type_system.definition_of<std::uint64_t>()));

		_symbols.insert(std::make_pair(util::from_cstring("float32"), _type_system.definition_of<float>()));
		_symbols.insert(std::make_pair(util::from_cstring("float64"), _type_system.definition_of<double>()));

		_symbols.insert(std::make_pair(util::from_cstring("string"), _type_system.definition_of<std::string>()));
	}
	void put_import(String_key name, Typed_object object)
	{
		if (_modules.find(name) != _modules.end()) {
			// TODO change error code
			BIA_THROW(error::Code::symbol_already_declared);
		}

		type::Variable variable{};
		auto tmp            = finish_typed_object(std::move(object));
		variable.offset     = store(_gc.create<member::Object>(std::move(tmp.first)));
		variable.definition = tmp.second;
		_modules.insert({ std::move(name), variable });
	}
	util::Optional<type::Variable> get_module(const String_key& name) const noexcept
	{
		const auto it = _modules.find(name);
		return it == _modules.end() ? util::Optional<type::Variable>{} : it->second;
	}

private:
	std::map<String_key, type::Variable> _modules;
};

} // namespace internal
} // namespace bia

#endif
