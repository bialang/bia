#include "helpers.hpp"

#include <bia/util/contract.hpp>
#include <tuple>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::decl_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Keyword::let);

	int flags = 0;
	if (tokens.at(1).value == Token::Keyword::mut) {
		flags |= symbol::Variable::flag_mutable;
		tokens = tokens.subspan(1);
	}

	const auto variable_token                      = tokens.at(1);
	tokens                                         = tokens.subspan(2);
	const internal::type::Definition* desired_type = nullptr;

	// process type definition available -> declare
	if (tokens.front().value != Operator::assign) {
		std::tie(tokens, desired_type) = type_definition(param, tokens);
		// continue on error
	}

	auto expr = single_expression(param, tokens.subspan(1));
	if (expr.second) {
		expr.second->flags = flags;

		if (desired_type && !desired_type->is_assignable(expr.second->definition)) {
			param.errors.add_error(error::Code::type_mismatch,
			                       tokens.subspan(1, tokens.size() - expr.first.size() - 1));
			param.symbols.free_temporary(*expr.second);
		} else if (!param.symbols.promote_temporary(variable_token.value.get<Token::Identifier>().memory,
		                                            *expr.second)) {
			param.errors.add_error(error::Code::symbol_already_declared, { &variable_token, 1 });
			param.symbols.free_temporary(*expr.second);
		}
	}
	return expr.first;
}
