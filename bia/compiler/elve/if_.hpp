#ifndef BIA_COMPILER_ELVE_IF_HPP_
#define BIA_COMPILER_ELVE_IF_HPP_

#include "../jump_manager.hpp"
#include "batch.hpp"
#include "expression.hpp"
#include "present.hpp"

#include <bia/util/finally.hpp>

namespace bia {
namespace compiler {
namespace elve {

inline tokens_type if_(present present, tokens_type tokens)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() && is_keyword(tokens.data(), token::keyword::if_));

	jump_manager jumper{ &present.writer.output() };
	const bytecode::member::local condition{ present.variables.add_tmp().id };
	auto finally = util::make_finally([&] { present.variables.remove_tmp(); });
	tokens       = expression(present, tokens.subspan(1), condition);

	present.writer.write<true, bytecode::oc_test>(
	    static_cast<typename std::underlying_type<member::test_operator>::type>(member::test_operator::self),
	    condition, condition);
	jumper.jump(jump_manager::type::if_false, jump_manager::destination::next);

	// process batch
	tokens = batch(present, tokens);

	jumper.jump(jump_manager::type::unconditional, jump_manager::destination::end);
	jumper.mark(jump_manager::destination::next);

	// do all else if
	while (!tokens.empty() && is_keyword(tokens.data(), token::keyword::else_if)) {
		tokens = expression(present, tokens.subspan(1), condition);

		present.writer.write<true, bytecode::oc_test>(
		    static_cast<typename std::underlying_type<member::test_operator>::type>(
		        member::test_operator::self),
		    condition, condition);
		jumper.jump(jump_manager::type::if_false, jump_manager::destination::next);

		// process batch
		tokens = batch(present, tokens);

		jumper.jump(jump_manager::type::unconditional, jump_manager::destination::end);
		jumper.mark(jump_manager::destination::next);
	}

	// check for else
	if (!tokens.empty() && is_keyword(tokens.data(), token::keyword::else_)) {
		// process batch
		tokens = batch(present, tokens.subspan(1));
	}

	jumper.mark(jump_manager::destination::end);

	return tokens;
} // namespace elve

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
