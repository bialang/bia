#ifndef BIA_COMPILER_ELVE_HELPERS_HPP_
#define BIA_COMPILER_ELVE_HELPERS_HPP_

#include "../symbol/manager.hpp"

#include <bia/bytecode/instructor.hpp>
#include <bia/tokenizer/token/token.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <cstdint>

namespace bia {
namespace compiler {
namespace elve {

struct Parameter
{
	bytecode::Instructor& instructor;
	symbol::Manager& symbols;
};

typedef util::span<const tokenizer::token::Token*> Tokens_type;

Tokens_type root(parameter& param, Tokens_type tokens);

Tokens_type decl_stmt(parameter& param, Tokens_type tokens);

std::pair<Tokens_type, util::Not_null<type::Definition*>>
  single_expression(Parameter& param, Tokens_type tokens, destination_type destination, bool atomic);

std::pair<Tokens_type, util::Not_null<type::definition*>> type_definition(parameter& param,
                                                                          Tokens_type tokens);

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
