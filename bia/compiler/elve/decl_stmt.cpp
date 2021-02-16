#include "helpers.hpp"

#include <bia/util/contract.hpp>
#include <tuple>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::decl_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Keyword::let);

	const auto& variable_name      = tokens.at(1).value.get<Token::Identifier>().memory;
	tokens                         = tokens.subspan(2);
	type::Definition* desired_type = nullptr;

	// process type definition available -> declare
	if (tokens.front().value != Operator::assign) {
		std::tie(tokens, desired_type) = type_definition(param, tokens);
		// continue on error
	}

	auto expr = single_expression(param, tokens.subspan(1));
	if (desired_type && !desired_type->is_assignable(expr.second.definition)) {
		param.errors.add_error(error::Code::type_mismatch,
		                       tokens.subspan(1, tokens.size() - expr.first.size() - 1));
		param.symbols.free_temporary(expr.second);
	} else {
		param.symbols.promote_temporary(variable_name, expr.second);
	}
	return expr.first;
}
