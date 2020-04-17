#include "compiler/variable_manager.hpp"

#include <util/gsl.hpp>
#include <util/limit_checker.hpp>

using namespace bia::compiler;

std::pair<variable_manager::variable, bool> variable_manager::index_of(const resource::view& identifier)
{
	// search for identifier
	for (auto i = static_cast<scope_index_type>(_scopes.size()); i--;) {
		const auto& scope = _scopes[i];
		const auto result = scope.variables.find(identifier);

		if (result != scope.variables.end()) {
			return { { i, result->second }, true };
		}
	}

	return { {}, false };
}

variable_manager::variable variable_manager::add(const resource::view& identifier)
{
	BIA_EXPECTS(!_scopes.empty());

	auto& scope = _scopes.back();

	scope.variables.insert({ identifier, scope.index });

	BIA_EXPECTS(util::limit_checker<index_type>::in_bounds(scope.index + 1));

	return { static_cast<scope_index_type>(_scopes.size() - 1), scope.index++ };
}

void variable_manager::open_scope()
{
	BIA_EXPECTS(util::limit_checker<scope_index_type>::in_bounds(_scopes.size() + 1));

	_scopes.push_back({});
}

void variable_manager::close_scope()
{
	_scopes.pop_back();
}
