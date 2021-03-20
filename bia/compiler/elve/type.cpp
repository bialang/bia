#include "helpers.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;
using namespace bia::internal;

std::pair<elve::Tokens, const type::Definition*> elve::type_definition(Parameter& param,
                                                                                Tokens tokens)
{
	// TODO
	BIA_EXPECTS(tokens.size() > 2 && tokens.front().value == Token::Control::type_definition &&
	            tokens[1].value.is_type<Token::Array_dimension>());
	const auto type = param.symbols.symbol(tokens.at(2).value.get<Token::Identifier>().memory);
	const type::Definition* definition = nullptr;
	// TODO array
	if (type.empty()) {
		param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(2, 1));
	} else if (!type.is_type<const type::Definition*>()) {
		param.errors.add_error(error::Code::symbol_not_a_type, tokens.subspan(2, 1));
	} else {
		definition = type.get<const type::Definition*>();
	}
	return { tokens.subspan(3), definition };
}
