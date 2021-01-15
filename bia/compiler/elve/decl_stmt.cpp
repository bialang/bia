#include "helpers.hpp"

#include <bia/util/contract.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens_type elve::decl_stmt(parameter& param, Tokens_type tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::keyword::let);

	auto variable = param.symbols.declare(tokens.at(1).value.get<token::identifier>().memory);
	tokens        = tokens.subspan(2);

	// process type definition
	if (tokens.front().value != operator_::assign) {
		type::definition* def;
		std::tie(tokens, def) = type_definition(param, tokens);
		variable.definition(def);
	}

	BIA_EXPECTS(tokens.front().value == operator_::assign);
	// TODO make util assignable from subset
	const auto expr =
	  single_expression(param, tokens.subspan(1), variable.location().get<bytecode::member::local>(), false);

	// check types
	if (variable.definition() && !variable.definition()->is_assignable(expr.second.get())) {
		BIA_THROW(error::Code::type_mismatch);
	}
	variable.definition(expr.second.get());
	variable.build();
	return expr.first;
}
