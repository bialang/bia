#include "compiler/compiler.hpp"

#include "compiler/elve/statement.hpp"

#include <exception/implementation_error.hpp>
#include <initializer_list>
#include <log/log.hpp>
#include <util/gsl.hpp>

using namespace bia::compiler;

compiler::compiler(std::ostream& instructions, std::ostream& resource) noexcept
    : _writer{ instructions }, _resources{ resource }
{
	// open the script scope
	_variables.open_scope();
}

void compiler::finish()
{
	_writer.finish();
	_resources.finish();
}

void compiler::receive(util::span<const token> tokens)
{
	for (const auto& i : tokens) {
		BIA_LOG(TRACE, "token {} is a {}", static_cast<const void*>(&i),
		        std::initializer_list<const char*>{
		            "cmd_end",
		            "identifier",
		            "batch",
		            "control",
		            "keyword",
		            "operator_",
		            "constant_string",
		            "constant_int",
		            "constant_float",
		        }
		            .begin()[i.value.index()]);
	}

	while (!tokens.empty()) {
		tokens = elve::statement({ _variables, _writer, _resources }, tokens);
	}
}
