#include "helpers.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::root(Parameter& param, Tokens tokens)
{
	if (tokens.front().value.is_type<Token::Keyword>()) {
		switch (tokens.front().value.get<Token::Keyword>()) {
		case Token::Keyword::let: tokens = decl_stmt(param, tokens); break;
		case Token::Keyword::if_: tokens = if_stmt(param, tokens); break;
		case Token::Keyword::import: tokens = import_stmt(param, tokens); break;
		default: BIA_THROW(error::Code::bad_switch_value);
		}
	} else {
		util::Optional<symbol::Variable> variable;
		std::tie(tokens, variable) = single_expression(param, tokens);
		if (variable) {
			param.symbols.free_temporary(*variable);
		}
	}
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Control::cmd_end);
	param.errors.reset_fail();
	return tokens.subspan(1);
}

elve::Tokens elve::batch(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value.is_type<Token::Batch>());
	param.symbols.open_scope();
	auto i = tokens.front().value.get<Token::Batch>().statement_count;
	tokens = tokens.subspan(1);
	while (i--) {
		tokens = root(param, tokens);
	}
	param.symbols.close_scope();
	return tokens;
}
