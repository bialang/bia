#include "helpers.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

std::pair<elve::Tokens_type, bia::util::Not_null<type::Definition*>> elve::type_definition(Parameter& param,
                                                                                           Tokens_type tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::control::type_definition);
	// const auto type = param.type_system.get(tokens.at(1).value.get<token::identifier>().memory);
	// if (!type) {
	// 	BIA_THROW(error::code::unknown_type);
	// }
	// return { tokens.subspan(2), type };
	return {tokens, (type::definition*)nullptr};
}
