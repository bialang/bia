#include "helpers.hpp"

#include <bia/error/exception.hpp>
#include <bia/internal/type/union.hpp>
#include <vector>

using namespace bia::compiler;
using namespace bia::tokenizer::token;
using namespace bia::internal;

std::pair<elve::Tokens, const type::Definition_base*> elve::type_definition(Parameter& param, Tokens tokens)
{
	// TODO
	BIA_EXPECTS(tokens.size() > 2 && tokens.front().value == Token::Control::type_definition &&
	            tokens[1].value.is_type<Token::Array_dimension>());
	tokens = tokens.subspan(1);
	std::vector<const type::Definition_base*> definitions;
	while (tokens.front().value.is_type<Token::Array_dimension>()) {
		const auto type = param.symbols.symbol(tokens.at(1).value.get<Token::Identifier>().memory);

		if (type.empty()) {
			param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(+0, 2));
		} else if (!type.is_type<const type::Definition_base*>()) {
			param.errors.add_error(error::Code::symbol_not_a_type, tokens.subspan(+0, 2));
		} else {
			definitions.push_back(type.get<const type::Definition_base*>());
		}
		tokens = tokens.subspan(2);
	}
	if (definitions.size() <= 1) {
		return { tokens, definitions.empty() ? nullptr : definitions.front() };
	}
	return { tokens, param.context.global_namespace().type_system().register_definition(
		                 internal::type::Definition<internal::type::Dynamic_union>{ std::move(definitions) }) };
}
