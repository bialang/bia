#include "variable.hpp"

#include <bia/util/contract.hpp>

using namespace bia::compiler::manager;

std::pair<variable::variable_type, bool> variable::find(const resource::view& identifer) noexcept
{
	// search overshadowers
	{
		const auto result = _overshadower.find(identifer);

		if (result != _overshadower.end()) {
			return { { result->second, type::local }, true };
		}
	}

	// normal variables
	const auto result = _variables.find(identifer);

	if (result != _variables.end()) {
		return { result->second, true };
	}

	// ask parent
	if (_parent) {
		const auto r = _parent->find(identifer);

		// add mapping; always take next because holes can be reused (whatever this means)
		if (r.second) {
			BIA_EXPECTS(r.first.second == type::local);
			_variables.insert({ identifer, { _next, r.first.second } });
			_bindings.push_back({ r.first.first, _next });

			return { { _next++, r.first.second }, true };
		}
	}

	return { { 0, {} }, false };
}

variable::index_type variable::add(resource::view identifer, type type)
{
	BIA_EXPECTS(_variables.find(identifer) == _variables.end());

	index_type index;

	if (_holes.empty()) {
		index = _next++;
	} else {
		index = *_holes.begin();

		_holes.erase(_holes.begin());
	}

	_variables.insert({ std::move(identifer), { index, type } });

	return index;
}

variable::index_type variable::add_overshadower(resource::view identifer)
{
	BIA_EXPECTS(_overshadower.find(identifer) == _overshadower.end());

	index_type index;

	if (_holes.empty()) {
		index = _next++;
	} else {
		index = *_holes.begin();

		_holes.erase(_holes.begin());
	}

	_overshadower.insert({ std::move(identifer), index });

	return index;
}

variable::index_type variable::add_tmp()
{
	// free holes open...
	if (!_holes.empty()) {
		const auto tmp = *_holes.begin();

		_holes.erase(_holes.begin());

		return tmp;
	}

	return _next++;
}

variable variable::open_scope()
{
	variable v;

	v._parent = this;

	return v;
}

void variable::remove_tmp(index_type index)
{
	_holes.insert(index);

	// check for chain
	auto i = _holes.rbegin();
	auto c = _next;

	while (i != _holes.rend() && *i != c - 1) {
		++i;
		--c;
	}

	if (c != _next) {
		_holes.erase(i.base(), _holes.end());

		_next = c;
	}
}

void variable::remove_overshadower(const resource::view& identifer)
{
	const auto result = _overshadower.find(identifer);

	if (result != _overshadower.end()) {
		const auto index = result->second;

		_overshadower.erase(result);

		remove_tmp(index);
	}
}

const std::vector<std::pair<variable::index_type, variable::index_type>>& variable::bindings() const noexcept
{
	return _bindings;
}
