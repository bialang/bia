#include "variable.hpp"

using namespace bia::compiler::manager;

std::pair<variable::index_type, bool> variable::find(const resource::view& identifer) noexcept
{
	const auto result = _variables.find(identifer);

	if (result == _variables.end()) {
		return { 0, false };
	}

	return { result->second, true };
}

variable::index_type variable::add(resource::view identifer)
{
	BIA_EXPECTS(_variables.find(identifer) == _variables.end());

	index_type index;

	if (_holes.empty()) {
		index = _next++;
	} else {
		index = *_holes.begin();

		_holes.erase(_holes.begin());
	}

	_variables.insert({ std::move(identifer), index });

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

variable::index_type variable::push() noexcept
{
	return _arguments++;
}

void variable::pop(std::size_t count)
{
	BIA_EXPECTS(count <= _arguments);

	_arguments -= count;
}

variable::index_type variable::latest_index() const
{
	BIA_EXPECTS(_next);

	return _next - 1;
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
