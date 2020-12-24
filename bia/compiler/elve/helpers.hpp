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

struct parameter
{
	bytecode::Instructor<std::uint32_t>& writer;
	symbol::manager& symbols;
};

typedef util::variant<bytecode::member::local, bytecode::member::args, bytecode::member::push>
  destination_type;
typedef util::span<const tokenizer::token::token*> tokens_type;

tokens_type root(parameter& param, tokens_type tokens);

tokens_type decl_stmt(parameter& param, tokens_type tokens);

std::pair<tokens_type, util::not_null<type::definition*>>
  single_expression(parameter& param, tokens_type tokens, destination_type destination, bool atomic);

std::pair<tokens_type, util::not_null<type::definition*>> type_definition(parameter& param,
                                                                          tokens_type tokens);

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
