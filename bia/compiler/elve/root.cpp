#include "helpers.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::tokens_type elve::root(parameter& param, tokens_type tokens)
{
	if (tokens.front().value.is_type<token::keyword>()) {
		switch (tokens.front().value.get<token::keyword>()) {
		case token::keyword::let: tokens = decl_stmt(param, tokens); break;
		default: BIA_THROW(error::code::bad_switch_value);
		}
	}
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == token::control::cmd_end);
	return tokens.subspan(1);
}
