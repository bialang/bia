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
		case Token::Keyword::while_: tokens = while_stmt(param, tokens); break;
		case Token::Keyword::import: tokens = import_stmt(param, tokens); break;
		case Token::Keyword::drop: tokens = drop_stmt(param, tokens); break;
		case Token::Keyword::scope: tokens = scope_stmt(param, tokens); break;
		case Token::Keyword::break_:
		case Token::Keyword::continue_: tokens = flow_control_stmt(param, tokens); break;
		default: BIA_THROW(error::Code::bad_switch_value);
		}
	} else if (tokens.front().value.is_type<Token::Statement_type>()) {
		switch (tokens.front().value.get<Token::Statement_type>()) {
		case Token::Statement_type::assign_statement: tokens = assign_stmt(param, tokens); break;
		default: BIA_THROW(error::Code::bad_switch_value);
		}
	} else {
		util::Optional<symbol::Local_variable> variable;
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
	close_scope(param);
	return tokens;
}

void elve::close_scope(Parameter& param)
{
	for (const auto& local : param.symbols.close_scope()) {
		if (!local.used) {
			param.warnings.add(error::Code::unused_variable, local.declare_range);
		}
	}
}
