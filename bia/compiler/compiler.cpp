#include "compiler.hpp"

#include "elve/helpers.hpp"

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
}
