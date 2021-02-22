#include "compiler.hpp"

#include "elve/helpers.hpp"

#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>

using namespace bia::compiler;

Compiler::Compiler(util::Not_null<std::shared_ptr<memory::Allocator>> allocator, std::ostream& instructions,
                   std::ostream& resource, internal::Context& context) noexcept
    : _instructor{ instructions }, _symbols{ allocator, symbol::Default_int_size::size_32 },
      _serializer{ resource }, _context{ context }
{}

void Compiler::receive(util::Span<const Token*> tokens, resource::Manager& manager)
{
	elve::Parameter params{ _instructor, _symbols, _serializer, _errors, _context };
	while (!tokens.empty()) {
		tokens = elve::root(params, tokens);
	}
}

const Errors& Compiler::errors() const noexcept
{
	return _errors;
}
