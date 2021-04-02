#ifndef BIA_COMPILER_ELVE_HELPERS_HPP_
#define BIA_COMPILER_ELVE_HELPERS_HPP_

#include "../errors.hpp"
#include "../flow_controller.hpp"
#include "../symbol/manager.hpp"

#include <bia/bytecode/instructor.hpp>
#include <bia/internal/context.hpp>
#include <bia/internal/type/definition.hpp>
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
	internal::Context& context;
	Flow_controller& flow_controller;
};

typedef util::Span<const tokenizer::token::Token*> Tokens;

Tokens root(Parameter& param, Tokens tokens);
Tokens batch(Parameter& param, Tokens tokens);

Tokens decl_stmt(Parameter& param, Tokens tokens);
Tokens if_stmt(Parameter& param, Tokens tokens);
Tokens while_stmt(Parameter& param, Tokens tokens);
Tokens import_stmt(Parameter& param, Tokens tokens);
Tokens flow_control_stmt(Parameter& param, Tokens tokens);

std::pair<Tokens, util::Optional<symbol::Variable>> value(Parameter& param, Tokens tokens);
std::pair<Tokens, util::Optional<symbol::Variable>> single_expression(Parameter& param, Tokens tokens);

std::pair<Tokens, util::Optional<symbol::Variable>>
  member_invocation(Parameter& param, Tokens tokens, symbol::Variable function, Tokens function_tokens);
std::pair<Tokens, util::Optional<symbol::Variable>>
  member_access(Parameter& param, Tokens tokens, symbol::Variable member, Tokens member_tokens);

std::pair<Tokens, const internal::type::Definition*> type_definition(Parameter& param, Tokens tokens);

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
