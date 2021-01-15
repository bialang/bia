#include "helpers.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens_type elve::root(parameter& param, Tokens_type tokens)
{
	if (tokens.front().value.is_type<token::keyword>()) {
		switch (tokens.front().value.get<token::keyword>()) {
		case token::keyword::let: tokens = decl_stmt(param, tokens); break;
		default: BIA_THROW(error::Code::bad_switch_value);
		}
	}
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::control::cmd_end);
	return tokens.subspan(1);
}
