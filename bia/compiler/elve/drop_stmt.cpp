#include "helpers.hpp"

#include <bia/util/contract.hpp>
#include <tuple>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::drop_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(tokens.front().value == Token::Keyword::drop);

	// TODO support multiple drops at the same time
	const auto error = param.symbols.drop_symbol(tokens.at(1).value.get<Token::Identifier>().memory);
	if (error != error::Code::success) {
		param.errors.add_error(error, tokens.subspan(1, 1));
	}
	return tokens.subspan(2);
}
