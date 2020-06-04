#ifndef BIA_COMPILER_ELVE_WHILE_HPP_
#define BIA_COMPILER_ELVE_WHILE_HPP_

#include "../jump_manager.hpp"
#include "expression.hpp"
#include "present.hpp"

namespace bia {
namespace compiler {
namespace elve {

tokens_type statement(present present, tokens_type tokens);

inline tokens_type while_(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	jump_manager manager{ &present.writer.output() };

	manager.mark(jump_manager::destination::start);

	tokens = expression(present, tokens.subspan(1), bytecode::member::tos{});

	auto count = tokens.data()->value.get<token::batch>().count;

	present.writer.write<true, bytecode::oc_test>(bytecode::member::tos{});
	present.writer.write<true, bytecode::oc_drop>(1);
	manager.jump(jump_manager::type::if_false, jump_manager::destination::end);

	tokens = tokens.subspan(1);

	while (count--) {
		// flow control
		if (static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword) {
			switch (tokens.data()->value.get<token::keyword>()) {
			case token::keyword::break_:
				manager.jump(jump_manager::type::unconditional, jump_manager::destination::end);
				break;
			case token::keyword::continue_:
				manager.jump(jump_manager::type::unconditional, jump_manager::destination::start);
				break;
			default: goto gt_continue;
			}

			BIA_EXPECTS(tokens.size() >= 2 &&
			            static_cast<token::type>(tokens.data()[1].value.index()) == token::type::cmd_end);

			tokens = tokens.subspan(2);
		} else {
		gt_continue:;
			tokens = statement(present, tokens);
		}
	}

	manager.jump(jump_manager::type::unconditional, jump_manager::destination::start);
	manager.mark(jump_manager::destination::end);

	return tokens;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
