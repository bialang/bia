#include "../jump_manager.hpp"
#include "expression.hpp"
#include "helpers.hpp"

#include <bia/util/finally.hpp>

bia::compiler::elve::tokens_type bia::compiler::elve::if_(present present, tokens_type tokens)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() && is_keyword(tokens.data(), token::keyword::if_));

	jump_manager jumper{ &present.writer.output() };
	const bytecode::member::local condition{ present.variables.add_tmp() };
	auto finally = util::make_finally([&] { present.variables.remove_tmp(condition.index); });
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
}
