#include "../jumper.hpp"
#include "helpers.hpp"

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::if_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Keyword::if_);

	Jumper jumper{ param.instructor };

	// if and every following else if statements
	do {
		symbol::Variable variable;
		std::tie(tokens, variable) = single_expression(param, tokens.subspan(1));

		// test expression
		if ((variable.definition->flags() & type::Definition::flag_truthable) !=
		    type::Definition::flag_truthable) {
			BIA_THROW(error::Code::type_not_truthable);
		}
		// TODO size of op code
		switch (variable.definition->size()) {
		case 1: param.instructor.write<bytecode::Op_code::truthy, std::int8_t>(variable.location.offset); break;
		case 2: param.instructor.write<bytecode::Op_code::truthy, std::int16_t>(variable.location.offset); break;
		case 4: param.instructor.write<bytecode::Op_code::truthy, std::int32_t>(variable.location.offset); break;
		case 8: param.instructor.write<bytecode::Op_code::truthy, std::int64_t>(variable.location.offset); break;
		default: BIA_THROW(error::Code::bad_switch_value);
		}

		param.symbols.free_temporary(variable);
		jumper.jump(Jumper::Type::if_false, Jumper::Destination::next);
		// statements
		tokens = batch(param, tokens);
		jumper.jump(Jumper::Type::unconditional, Jumper::Destination::end);
		jumper.mark(Jumper::Destination::next);
	} while (!tokens.empty() && tokens.front().value == Token::Keyword::else_if);

	// else statement
	if (!tokens.empty() && tokens.front().value == Token::Keyword::else_) {
		tokens = batch(param, tokens.subspan(1));
	}

	jumper.mark(Jumper::Destination::end);
	return tokens;
}
