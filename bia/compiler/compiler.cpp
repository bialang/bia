#include "compiler.hpp"

#include "elve/helpers.hpp"

#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>

using namespace bia::compiler;

Compiler::Compiler(std::ostream& instructions) noexcept
    : _instructor{ instructions }
{}

void Compiler::receive(util::span<const token*> tokens, resource::Manager& manager)
{
	elve::Parameter params{ _instructor, _symbols };
	while (!tokens.empty()) {
		tokens = elve::root(params, tokens);
	}
}
