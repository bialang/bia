#include "helpers.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

std::pair<elve::tokens_type, bia::util::not_null<type::definition*>> elve::type_definition(parameter& param,
                                                                                           tokens_type tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == token::control::type_definition);
	const auto type = param.type_system.get(tokens.at(1).value.get<token::identifier>().memory);
	if (!type) {
		BIA_THROW(error::code::unknown_type);
	}
	return { tokens.subspan(2), type };
}
