#include "compiler.hpp"

#include "elve/helpers.hpp"

#include <bia/exception/implementation_error.hpp>
#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>
#include <initializer_list>

using namespace bia::compiler;

compiler::compiler(std::ostream& instructions, std::ostream& resource) noexcept
    : _writer{ instructions }, _resources{ resource }
{}

void compiler::finish()
{
	_writer.finish();
	_resources.finish();
}

void compiler::receive(util::span<const token*> tokens, resource::manager& manager)
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
		            "constant_regex",
		            "constant_int",
		            "constant_float",
		        }
		            .begin()[i.value.index()]);
	}

	while (!tokens.empty()) {
		tokens = elve::statement({ _variables, _writer, _resources, manager }, tokens);
	}
}
