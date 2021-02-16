#include "helpers.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

std::pair<elve::Tokens, type::Definition*> elve::type_definition(Parameter& param, Tokens tokens)
{
	// TODO
	BIA_EXPECTS(tokens.size() > 2 && tokens.front().value == Token::Control::type_definition &&
	            tokens[1].value.is_type<Token::Array_dimension>());
	const auto type = param.symbols.symbol(tokens.at(2).value.get<Token::Identifier>().memory);
	if (type.empty()) {
		param.errors.add_error(error::Code::undefined_symbol, tokens.at(2));
	} else if (!type.is_type<type::Definition*>()) {
		param.errors.add_error(error::Code::symbol_not_a_type, tokens.at(2));
	}
	return { tokens.subspan(3), type.get<type::Definition*>() };
}
