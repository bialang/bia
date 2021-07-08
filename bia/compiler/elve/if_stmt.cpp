#include "../jumper.hpp"
#include "helpers.hpp"

using namespace bia::compiler;
using namespace bia::tokenizer::token;
using namespace bia::internal;

elve::Tokens elve::if_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Keyword::if_);

	Jumper jumper{ param.instructor };

	// if and every following else if statements
	do {
		util::Optional<symbol::Variable> variable;
		auto expression_tokens     = tokens.subspan(1);
		std::tie(tokens, variable) = single_expression(param, expression_tokens);
		expression_tokens          = expression_tokens.left(tokens.begin());

		if (variable) {
			if (!dynamic_cast<const type::Bool*>(variable->definition)) {
				param.errors.add_error(error::Code::type_mismatch, expression_tokens.left(tokens.begin()));
			}

			param.symbols.free_temporary(*variable);
			jumper.jump(Jumper::Type::if_false, Jumper::Destination::next);
			// statements
			tokens = batch(param, tokens);
			jumper.jump(Jumper::Type::unconditional, Jumper::Destination::end);
			jumper.mark(Jumper::Destination::next);
		}
	} while (!tokens.empty() && tokens.front().value == Token::Keyword::else_if);

	// else statement
	if (!tokens.empty() && tokens.front().value == Token::Keyword::else_) {
		tokens = batch(param, tokens.subspan(1));
	}

	jumper.mark(Jumper::Destination::end);
	return tokens;
}
