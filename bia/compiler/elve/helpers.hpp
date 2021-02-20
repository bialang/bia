#ifndef BIA_COMPILER_ELVE_HELPERS_HPP_
#define BIA_COMPILER_ELVE_HELPERS_HPP_

#include "../errors.hpp"
#include "../symbol/manager.hpp"

#include <bia/bvm/context.hpp>
#include <bia/bytecode/instructor.hpp>
#include <bia/resource/serializer.hpp>
#include <bia/tokenizer/token/token.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/optional.hpp>
#include <bia/util/variant.hpp>
#include <cstdint>

namespace bia {
namespace compiler {
namespace elve {

struct Parameter
{
	bytecode::Instructor& instructor;
	symbol::Manager& symbols;
	resource::Serializer& serializer;
	Errors& errors;
	bvm::Context& context;
};

typedef util::Span<const tokenizer::token::Token*> Tokens;

Tokens root(Parameter& param, Tokens tokens);
Tokens batch(Parameter& param, Tokens tokens);

Tokens decl_stmt(Parameter& param, Tokens tokens);
Tokens if_stmt(Parameter& param, Tokens tokens);
Tokens import_stmt(Parameter& param, Tokens tokens);

std::pair<Tokens, symbol::Variable> single_expression(Parameter& param, Tokens tokens);
std::pair<Tokens, type::Definition*> type_definition(Parameter& param, Tokens tokens);

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
