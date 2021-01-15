#include "manager.hpp"

#include <bia/compiler/type/integer.hpp>
#include <bia/error/exception.hpp>

using namespace bia::compiler::symbol;

Manager::Manager()
{
	// there is always a global scope
	_scopes.emplace_back();
}

void Manager::open_scope()
{
	_scopes.emplace_back();
}

void Manager::close_scope()
{
	BIA_EXPECTS(_scopes.size() > 1);
	for (const auto& it : _scopes.back()) {
		_symbols.erase(it);
	}
	_scopes.pop_back();
}

Builder Manager::declare(const resource::View& name)
{
	if (_symbols.find(name) != _symbols.end() || _declared.find(name) != _declared.end()) {
		BIA_THROW(error::Code::symbol_already_declared);
	}
	// TODO add location
	_declared.insert({ name, Location{} });
	return { this, name, Location{} };
}

Symbol_type Manager::symbol(const resource::View& name)
{
	const auto result = _symbols.find(name);
	if (result == _symbols.end()) {
		return {};
	}
	return result->second;
}

Symbol_type Manager::symbol(const string_type& name)
{
	const auto result = _symbols.find(name);
	if (result == _symbols.end()) {
		return {};
	}
	return result->second;
}

bool Manager::Comparator::operator()(const map_key_type& left, const map_key_type& right) const
{
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

void Manager::_accept_declared(const resource::View& name, Variable var)
{
	const auto d = _declared.find(name);
	BIA_EXPECTS(d != _declared.end());
	_declared.erase(d);
	const auto it = _symbols.insert({ name, std::move(var) });
	_scopes.back().push_back(it.first);
}

void Manager::_decline_declared(const resource::View& name)
{
	const auto d = _declared.find(name);
	BIA_EXPECTS(d != _declared.end());
	_declared.erase(d);
}
