#include "manager.hpp"

#include <bia/error/exception.hpp>
#include <bia/internal/type/bool.hpp>
#include <bia/internal/type/regex.hpp>
#include <bia/internal/type/string.hpp>
#include <bia/internal/type/void.hpp>
#include <bia/util/algorithm.hpp>

using namespace bia;
using namespace bia::compiler::symbol;

Manager::Manager(util::Not_null<std::shared_ptr<memory::Allocator>> allocator,
                 const internal::Namespace& global_namespace, Default_int_size default_int_size)
    : _global_namespace{ global_namespace }
{
	_default_int_size = default_int_size;
	// there is always a global scope
	_scopes.emplace_back();
	// _introduce_native_types();
}

void Manager::open_scope()
{
	_scopes.emplace_back();
}

void Manager::close_scope()
{
	BIA_EXPECTS(_scopes.size() > 1);
	auto& scope = _scopes.back();
	for (auto i = scope.rbegin(); i != scope.rend(); ++i) {
		_drop(*i);
	}
	_scopes.pop_back();
}

error::Code Manager::drop_symbol(const internal::String_key& name)
{
	const auto it = _symbols.find(name);
	if (it == _symbols.end()) {
		return error::Code::undefined_symbol;
	}
	auto& scope = _scopes.back();
	for (auto i = scope.begin(); i != scope.end(); ++i) {
		if (*i == it) {
			// just remove from the symbols index
			_symbols.erase(it);
			return error::Code::success;
		}
	}
	return error::Code::symbol_defined_in_different_scope;
}

Local_variable Manager::create_temporary(util::Not_null<const internal::type::Definition_base*> type)
{
	Local_variable variable{};
	variable.definition = type;
	variable.offset     = _stack;
	variable.flags      = Local_variable::flag_mutable;
	_stack += util::aligned(type->size(), alignof(std::max_align_t));
	return variable;
}

void Manager::free_temporary(Local_variable variable)
{
	BIA_EXPECTS(variable.definition);
	// TODO solve alignment a more efficient way
	const auto size = util::aligned(variable.definition->size(), alignof(std::max_align_t));
	// TODO add support if variable is not at the end
	if (variable.offset + size == _stack) {
		_stack -= size;
	}
}

bool Manager::promote_temporary(const resource::View& name, const Local_variable& variable)
{
	if (_symbols.find({ name }) != _symbols.end() || !_global_namespace.global({ name }).empty()) {
		return false;
	}
	const auto it = _symbols.insert(std::make_pair(name, variable)).first;
	_scopes.back().push_back(it);
	return true;
}

Symbol Manager::symbol(const internal::String_key& name)
{
	const auto it = _symbols.find(name);
	if (it != _symbols.end()) {
		return it->second;
	}

	const auto symbol = _global_namespace.global(name);
	if (symbol.is_type<const internal::type::Definition_base*>()) {
		return symbol.get<const internal::type::Definition_base*>();
	} else if (symbol.is_type<internal::Global_variable>()) {
		return symbol.get<internal::Global_variable>();
	}
	return {};
}

void Manager::_accept_declared(const resource::View& name, Local_variable var)
{
	const auto d = _declared.find(name);
	BIA_EXPECTS(d != _declared.end());
	_declared.erase(d);
	const auto it = _symbols.insert(std::make_pair(name, std::move(var)));
	_scopes.back().push_back(it.first);
}

void Manager::_decline_declared(const resource::View& name)
{
	const auto d = _declared.find(name);
	BIA_EXPECTS(d != _declared.end());
	_declared.erase(d);
}

// void Manager::_introduce_native_types()
// {
// 	using namespace internal::type;

// 	if (_default_int_size == Default_int_size::size_32) {
// 		_symbols.insert(
// 		  std::make_pair(util::from_cstring("int"),
// 		                 static_cast<Definition*>(_type_system.create_type<Integer>(Integer::Size::i32,
// true)))); 		_symbols.insert( 		  std::make_pair(util::from_cstring("uint"),
// 		                 static_cast<Definition*>(_type_system.create_type<Integer>(Integer::Size::u32,
// true)))); 	} else { 		BIA_ASSERT(false);
// 	}

// 	_symbols.insert(
// 	  std::make_pair(util::from_cstring("void"), static_cast<Definition*>(_type_system.create_type<Void>())));

// 	_symbols.insert(
// 	  std::make_pair(util::from_cstring("bool"), static_cast<Definition*>(_type_system.create_type<Bool>())));

// 	_symbols.insert(
// 	  std::make_pair(util::from_cstring("int32"),
// 	                 static_cast<Definition*>(_type_system.create_type<Integer>(Integer::Size::i32, false))));

// 	_symbols.insert(std::make_pair(
// 	  util::from_cstring("float32"),
// 	  static_cast<Definition*>(_type_system.create_type<Floating_point>(Floating_point::Size::f32))));

// 	_symbols.insert(std::make_pair(util::from_cstring("string"),
// 	                               static_cast<Definition*>(_type_system.create_type<String>())));
// 	_symbols.insert(
// 	  std::make_pair(util::from_cstring("regex"),
// static_cast<Definition*>(_type_system.create_type<Regex>())));
// }

void Manager::_drop(map_type::const_iterator it)
{
	if (it->second.is_type<Local_variable>()) {
		const auto& variable = it->second.get<Local_variable>();
		// TODO better freeing
		if (variable.offset + variable.definition->size() == _stack) {
			_stack -= variable.definition->size();
		}
	}
	_symbols.erase(it);
}
