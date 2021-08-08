#ifndef BIA_INTERNAL_NAMESPACE_HPP_
#define BIA_INTERNAL_NAMESPACE_HPP_

#include "string_key.hpp"
#include "type/bool.hpp"
#include "type/function.hpp"
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

struct Variable_base
{
	enum Flag
	{
		flag_mutable = 0x1
	};

	std::size_t offset;
	const type::Definition_base* definition;
	int flags;
};

struct Global_variable : Variable_base
{};

class Namespace
{
public:
	Namespace(internal::type::System& type_system, memory::gc::GC& gc) noexcept
	    : _type_system{ type_system }, _gc{ gc },
	      _global_space{ static_cast<util::Byte*>(gc.allocator()->allocate(1024)), 1024 }, _global_frame{
		      _global_space, _gc, 0
	      }
	{
		// link Bia's data types to definitions
		_global_index.insert(std::make_pair(util::from_cstring("void"), _type_system.definition_of<void>()));
		_global_index.insert(std::make_pair(util::from_cstring("bool"), _type_system.definition_of<bool>()));

		_global_index.insert(
		  std::make_pair(util::from_cstring("int8"), _type_system.definition_of<std::int8_t>()));
		_global_index.insert(
		  std::make_pair(util::from_cstring("uint8"), _type_system.definition_of<std::uint8_t>()));

		_global_index.insert(
		  std::make_pair(util::from_cstring("int16"), _type_system.definition_of<std::int16_t>()));
		_global_index.insert(
		  std::make_pair(util::from_cstring("uint16"), _type_system.definition_of<std::uint16_t>()));

		_global_index.insert(
		  std::make_pair(util::from_cstring("int32"), _type_system.definition_of<std::int32_t>()));
		_global_index.insert(
		  std::make_pair(util::from_cstring("uint32"), _type_system.definition_of<std::uint32_t>()));

		_global_index.insert(
		  std::make_pair(util::from_cstring("int"), _type_system.definition_of<std::ptrdiff_t>()));
		_global_index.insert(
		  std::make_pair(util::from_cstring("uint"),
		                 _type_system.definition_of<typename std::make_unsigned<std::ptrdiff_t>::type>()));

		_global_index.insert(
		  std::make_pair(util::from_cstring("int64"), _type_system.definition_of<std::int64_t>()));
		_global_index.insert(
		  std::make_pair(util::from_cstring("uint64"), _type_system.definition_of<std::uint64_t>()));

		_global_index.insert(std::make_pair(util::from_cstring("float32"), _type_system.definition_of<float>()));
		_global_index.insert(std::make_pair(util::from_cstring("float64"), _type_system.definition_of<double>()));

		_global_index.insert(
		  std::make_pair(util::from_cstring("string"), _type_system.definition_of<std::string>()));
		// _global_index.insert(
		//   std::make_pair(util::from_cstring("string"),
		//                  static_cast<const Definition_base*>(_type_system.get_or_create<String>())));
		// _global_index.insert(std::make_pair(
		//   util::from_cstring("regex"), static_cast<const
		//   Definition_base*>(_type_system.get_or_create<Regex>())));
	}
	template<typename Type>
	void put_value(String_key name, Type&& value, bool immutable = true)
	{
		if (_global_index.find(name) != _global_index.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}

		const std::size_t written = _global_frame.store(_offset, std::forward<Type>(value));
		const auto definition     = _type_system.definition_of<Type>();
		Global_variable variable{};
		variable.offset     = _offset;
		variable.definition = definition;
		variable.flags      = immutable ? 0 : Global_variable::flag_mutable;
		_global_index.insert({ name, variable });
		_offset += util::aligned(written, alignof(std::max_align_t));
	}
	template<typename Invokeable>
	void put_invokable(String_key name, Invokeable&& invokable, bool immutable = true)
	{
		static_assert(util::type_traits::Invokable_info<Invokeable>::is_invokable,
		              "Invokeable must be a invokable");
		if (_global_index.find(name) != _global_index.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}

		// TODO alignment of types
		// TODO protect ptr from GC, because it cannot be collected in global namespace
		const auto ptr = member::function::create(_gc, std::forward<Invokeable>(invokable));
		_global_frame.store(_offset, ptr);
		const auto function_definition =
		  _type_system.definition_of<typename util::type_traits::Invokable_info<Invokeable>::Signature>();
		Global_variable variable{};
		variable.offset     = _offset;
		variable.definition = function_definition;
		variable.flags      = immutable ? 0 : Global_variable::flag_mutable;
		_global_index.insert({ name, variable });
		_offset += util::aligned(sizeof(ptr), alignof(std::max_align_t));
	}
	memory::Frame<true> globals() const
	{
		return _global_frame;
	}
	util::Variant<Global_variable, const type::Definition_base*> global(const String_key& name) const
	{
		const auto it = _global_index.find(name);
		if (it != _global_index.end()) {
			return it->second;
		}
		return {};
	}
	memory::gc::GC& gc() noexcept
	{
		return _gc;
	}

private:
	internal::type::System& _type_system;
	memory::gc::GC& _gc;
	std::size_t _offset = 0;
	util::Span<util::Byte*> _global_space;
	memory::Frame<true> _global_frame;
	/// Maps names to the global symbols relative to the global frame.
	std::map<String_key, util::Variant<Global_variable, const type::Definition_base*>, String_comparator>
	  _global_index;
};

} // namespace internal
} // namespace bia

#endif
