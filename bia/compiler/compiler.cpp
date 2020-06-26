#include "compiler.hpp"

#include "elve/statement.hpp"

#include <bia/exception/implementation_error.hpp>
#include <initializer_list>
#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>

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

void compiler::receive(util::span<const token*> tokens)
{
	for (const auto& i : tokens) {
		BIA_LOG(INFO, "token {} is a {}", static_cast<const void*>(&i),
		        std::initializer_list<const char*>{
		            "cmd_end",
		            "identifier",
					"builtin",
		            "batch",
		            "control",
		            "keyword",
		            "operator_",
		            "constant_string",
					"constant_regex",
		            "constant_int",
		            "constant_float",
		        }
		            .begin()[i.value.index()]);
	}

	while (!tokens.empty()) {
		tokens = elve::statement({ _variables, _writer, _resources }, tokens);
	}
}
