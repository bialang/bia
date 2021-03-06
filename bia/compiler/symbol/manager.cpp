#include "manager.hpp"

#include <bia/error/exception.hpp>
#include <bia/internal/type/bool.hpp>
#include <bia/internal/type/floating_point.hpp>
#include <bia/internal/type/integer.hpp>
#include <bia/internal/type/regex.hpp>
#include <bia/internal/type/string.hpp>
#include <bia/internal/type/void.hpp>
#include <bia/util/algorithm.hpp>

using namespace bia::compiler::symbol;

Manager::Manager(util::Not_null<std::shared_ptr<memory::Allocator>> allocator,
                 Default_int_size default_int_size)
    : _type_system{ allocator }
{
	_default_int_size = default_int_size;
	// there is always a global scope
	_scopes.emplace_back();
	_introduce_native_types();
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

Variable Manager::create_temporary(util::Not_null<const internal::type::Definition*> type)
{
	Variable variable{};
	variable.definition      = type;
	variable.location.offset = _stack;
	_stack += util::aligned(type->size(), alignof(std::max_align_t));
	return variable;
}

void Manager::free_temporary(Variable variable)
{
	BIA_EXPECTS(variable.definition);
	// TODO solve alignment a more efficient way
	const auto size = util::aligned(variable.definition->size(), alignof(std::max_align_t));
	// TODO add support if variable is not at the end
	if (variable.location.offset + size == _stack) {
		_stack -= size;
	}
}

bool Manager::promote_temporary(const resource::View& name, const Variable& variable)
{
	if (_symbols.find({ name }) != _symbols.end()) {
		return false;
	}
	const auto it = _symbols.insert(std::make_pair(name, variable)).first;
	_scopes.back().push_back(it);
	return true;
}

Symbol Manager::symbol(const resource::View& name)
{
	const auto result = _symbols.find(name);
	if (result == _symbols.end()) {
		return {};
	}
	return result->second;
}

Symbol Manager::symbol(const string_type& name)
{
	const auto result = _symbols.find(name);
	if (result == _symbols.end()) {
		return {};
	}
	return result->second;
}

bool Manager::Comparator::operator()(const map_key_type& left, const map_key_type& right) const
{
	const auto comp = [&] {
		if (left.is_type<resource::View>()) {
			if (right.is_type<resource::View>()) {
				return left.get<resource::View>() < right.get<resource::View>();
			}
			const auto str = right.get<string_type>();
			return left.get<resource::View>().compare(str.data(), str.size()) < 0;
		}
		const auto lstr = left.get<string_type>();
		if (right.is_type<resource::View>()) {
			return right.get<resource::View>().compare(lstr.data(), lstr.size()) > 0;
		}
		// both are strings
		const auto rstr = right.get<string_type>();
		return util::compare_ranges(lstr.begin(), lstr.end(), rstr.begin(), rstr.end()) < 0;
	};
	// printf("comp: left=");
	// if (left.is_type<resource::View>()) {
	// 	printf("r'");
	// 	for (auto i : left.get<resource::View>()) {
	// 		printf("%c", (char) i);
	// 	}
	// } else {
	// 	printf("'%s", left.get<string_type>().begin());
	// }
	// printf("', right=");
	// if (right.is_type<resource::View>()) {
	// 	printf("r'");
	// 	for (auto i : right.get<resource::View>()) {
	// 		printf("%c", (char) i);
	// 	}
	// } else {
	// 	printf("'%s", right.get<string_type>().begin());
	// }
	bool less = comp();
	// printf("', less=%s\n", less ? "yes" : "no");
	return less;
}

void Manager::_accept_declared(const resource::View& name, Variable var)
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

void Manager::_introduce_native_types()
{
	using namespace internal::type;

	if (_default_int_size == Default_int_size::size_32) {
		_symbols.insert(
		  std::make_pair(util::from_cstring("int"),
		                 static_cast<Definition*>(_type_system.create_type<Integer>(Integer::Size::i32, true))));
		_symbols.insert(
		  std::make_pair(util::from_cstring("uint"),
		                 static_cast<Definition*>(_type_system.create_type<Integer>(Integer::Size::u32, true))));
	} else {
		BIA_ASSERT(false);
	}

	_symbols.insert(
	  std::make_pair(util::from_cstring("void"), static_cast<Definition*>(_type_system.create_type<Void>())));

	_symbols.insert(
	  std::make_pair(util::from_cstring("bool"), static_cast<Definition*>(_type_system.create_type<Bool>())));

	_symbols.insert(
	  std::make_pair(util::from_cstring("int32"),
	                 static_cast<Definition*>(_type_system.create_type<Integer>(Integer::Size::i32, false))));

	_symbols.insert(std::make_pair(
	  util::from_cstring("float32"),
	  static_cast<Definition*>(_type_system.create_type<Floating_point>(Floating_point::Size::f32))));

	_symbols.insert(std::make_pair(util::from_cstring("string"),
	                               static_cast<Definition*>(_type_system.create_type<String>())));
	_symbols.insert(
	  std::make_pair(util::from_cstring("regex"), static_cast<Definition*>(_type_system.create_type<Regex>())));
}

void Manager::_drop(map_type::const_iterator it)
{
	if (it->second.is_type<symbol::Variable>()) {
		const auto& variable = it->second.get<symbol::Variable>();
		// TODO better freeing
		if (variable.location.offset + variable.definition->size() == _stack) {
			_stack -= variable.definition->size();
		}
	}
	_symbols.erase(it);
}
