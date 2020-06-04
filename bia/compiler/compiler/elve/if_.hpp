#ifndef BIA_COMPILER_ELVE_IF_HPP_
#define BIA_COMPILER_ELVE_IF_HPP_

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

	tokens = expression(present, tokens.subspan(1), bytecode::member::tos{}, -1);

	present.writer.write<true, bytecode::oc_test>(bytecode::member::tos{});
	present.writer.write<true, bytecode::oc_drop>(1);
	present.writer.write<false, bytecode::oc_jump_false>(std::int32_t{ 0 });

	// process batch
	tokens = batch(present, tokens);

	// do all else if

	// check for else

	return tokens;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
