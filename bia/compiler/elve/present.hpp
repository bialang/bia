#ifndef BIA_COMPILER_ELVE_PRESENT_HPP_
#define BIA_COMPILER_ELVE_PRESENT_HPP_

#include "../manager/variable.hpp"

#include <bia/bytecode/writer/instruction.hpp>
#include <bia/resource/serializer.hpp>
#include <bia/tokenizer/token/token.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace compiler {
namespace elve {

struct present
{
	manager::variable& variables;
	bytecode::writer::instruction& writer;
	resource::serializer& resources;
};

typedef util::span<const tokenizer::token::token*> tokens_type;

inline bool is_keyword(util::not_null<const tokenizer::token::token*> token,
                       tokenizer::token::token::keyword keyword) noexcept
{
	return static_cast<tokenizer::token::token::type>(token->value.index()) ==
	           tokenizer::token::token::type::keyword &&
	       token->value.get<tokenizer::token::token::keyword>() == keyword;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
