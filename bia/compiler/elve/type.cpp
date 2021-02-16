#include "helpers.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

std::pair<elve::Tokens, bia::util::Not_null<type::Definition*>> elve::type_definition(Parameter& param,
                                                                                      Tokens tokens)
{
	// TODO
	BIA_EXPECTS(tokens.size() > 2 && tokens.front().value == Token::Control::type_definition &&
	            tokens[1].value.is_type<Token::Array_dimension>());
	const auto type = param.symbols.symbol(tokens.at(2).value.get<Token::Identifier>().memory);
	if (type.empty()) {
		BIA_THROW(error::Code::undefined_symbol);
	} else if (!type.is_type<type::Definition*>()) {
		BIA_THROW(error::Code::symbol_not_a_type);
	}
	return { tokens.subspan(3), type.get<type::Definition*>() };
}
