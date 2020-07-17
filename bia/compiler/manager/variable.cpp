#include "variable.hpp"

using namespace bia::compiler::manager;

std::pair<variable::index_type, bool> variable::find(const resource::view& identifer)
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

variable::index_type variable::add_tmp(bool tos)
{
	// free holes open...
	if (!tos && !_holes.empty()) {
		const auto tmp = *_holes.begin();

		_holes.erase(_holes.begin());

		return tmp;
	}

	return _next++;
}

variable::index_type variable::latest_index() const
{
	BIA_EXPECTS(_next);

	return _next - 1;
}

bool variable::is_tos(index_type index) const noexcept
{
	return _next && _next - 1 == index;
}

std::uint8_t variable::remove_tmp(index_type index)
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

		const auto tmp = _next - c;
		_next          = c;

		return static_cast<std::uint8_t>(tmp);
	}

	return 0;
}

std::uint8_t variable::remove_overshadower(const resource::view& identifer)
{
	const auto result = _overshadower.find(identifer);

	if (result == _overshadower.end()) {
		return 0;
	}

	const auto index = result->second;

	_overshadower.erase(result);

	return remove_tmp(index);
}
