#include "compiler/variable_manager.hpp"

#include <util/gsl.hpp>

using namespace bia::compiler;

std::pair<variable_manager::scope_index_type, variable_manager::index_type>
    variable_manager::index_of(gc::memory::view identifier)
{
	BIA_EXPECTS(!_scopes.empty());

	// search for identifier
	for (auto i = _scopes.size(); i--;) {
		const auto& scope = _scopes[i];
		const auto result = scope.variables.find(identifier);

		if (result != scope.variables.end()) {
			return { i, result->second };
		}
	}

	// add new variable
	auto& scope = _scopes.back();

	scope.variables.insert({ std::move(identifier), scope.index });

	return { _scopes.size() - 1, scope.index++ };
}

variable_manager::scope_index_type variable_manager::current_scope() const
{
	BIA_EXPECTS(!_scopes.empty());

	return _scopes.size() - 1;
}

void variable_manager::open_scope()
{
	_scopes.push_back({});
}

void variable_manager::close_scope()
{
	_scopes.pop_back();
}
