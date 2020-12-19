#include "manager.hpp"

#include <bia/compiler/type/integer.hpp>
#include <bia/error/exception.hpp>

using namespace bia::compiler::symbol;

namespace {

using namespace bia::compiler;

type::integer int_type{ type::integer::size::i };

} // namespace

manager::manager()
{
	_scopes.emplace_back();

	// create native types
	_variables.insert({ string_type{ "int", 3 }, {} });
	_variables.insert({ string_type{ "uint", 4 }, {} });
	_variables.insert({ string_type{ "int8", 4 }, {} });
	_variables.insert({ string_type{ "uint8", 5 }, {} });
	_variables.insert({ string_type{ "int16", 5 }, {} });
	_variables.insert({ string_type{ "uint16", 6 }, {} });
	_variables.insert({ string_type{ "int32", 5 }, {} });
	_variables.insert({ string_type{ "uint32", 6 }, {} });
	_variables.insert({ string_type{ "int64", 5 }, {} });
	_variables.insert({ string_type{ "uint64", 6 }, {} });

	_variables.insert({ string_type{ "float32", 7 }, {} });
	_variables.insert({ string_type{ "float64", 7 }, {} });
}

void manager::open_scope()
{
	_scopes.emplace_back();
}

void manager::close_scope()
{
	BIA_EXPECTS(_scopes.size() > 1);
	for (const auto& it : _scopes.back()) {
		_variables.erase(it);
	}
	_scopes.pop_back();
}

builder manager::declare(const resource::view& name)
{
	if (_variables.find(name) != _variables.end() || _declared.find(name) != _declared.end()) {
		BIA_THROW(error::code::variable_alread_declared);
	}
	_declared.insert({ name, bytecode::member::local{ _index } });
	return { this, name, bytecode::member::local{ _index++ } };
}

bool manager::comparator::operator()(const map_key_type& left, const map_key_type& right) const
{
	if (left.is_type<resource::view>()) {
		if (right.is_type<resource::view>()) {
			return left.get<resource::view>() < right.get<resource::view>();
		}
		const auto str = right.get<string_type>();
		return left.get<resource::view>().compare(str.data(), str.size()) < 0;
	}
	const auto lstr = right.get<string_type>();
	if (right.is_type<resource::view>()) {
		return right.get<resource::view>().compare(lstr.data(), lstr.size()) > 0;
	}
	// both are strings
	const auto rstr = right.get<string_type>();
	if (lstr.size() < rstr.size()) {
		return true;
	} else if (lstr.size() > rstr.size()) {
		return false;
	}
	for (auto a = lstr.begin(), b = rstr.begin(); a != lstr.end(); ++a, ++b) {
		if (*a < *b) {
			return true;
		} else if (*a > *b) {
			return false;
		}
	}
	return false;
}

void manager::_accept_declared(const resource::view& name, variable var)
{
	_declared.erase(name);
	_variables.insert({ name, std::move(var) });
}

void manager::_decline_declared(const resource::view& name)
{
	_declared.erase(name);
}
