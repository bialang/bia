#ifndef BIA_COMPILER_ELVE_IF_HPP_
#define BIA_COMPILER_ELVE_IF_HPP_

#include "../jump_manager.hpp"
#include "batch.hpp"
#include "expression.hpp"
#include "present.hpp"

namespace bia {
namespace compiler {
namespace elve {

inline tokens_type if_(present present, tokens_type tokens)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword);

	jump_manager jumper{ &present.writer.output() };

	tokens = expression(present, tokens.subspan(1), bytecode::member::tos{}, -1);

	present.writer.write<true, bytecode::oc_test>(bytecode::member::tos{});
	present.writer.write<true, bytecode::oc_drop>(1);
	jumper.jump(jump_manager::type::if_false, jump_manager::destination::next);

	// process batch
	tokens = batch(present, tokens);

	jumper.jump(jump_manager::type::unconditional, jump_manager::destination::end);
	jumper.mark(jump_manager::destination::next);

	// do all else if

	// check for else

	jumper.mark(jump_manager::destination::end);

	return tokens;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
