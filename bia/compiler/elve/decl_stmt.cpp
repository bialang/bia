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
	}

	symbol::Variable variable;
	std::tie(tokens, variable) = single_expression(param, tokens.subspan(1));

	if (desired_type && !desired_type->is_assignable(variable.definition)) {
		BIA_THROW(error::Code::type_mismatch);
	}

	param.symbols.promote_temporary(variable_name, variable);
	return tokens;
}
