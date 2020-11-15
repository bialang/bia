#include "any_of.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

std::error_code bia::tokenizer::token::parse::type_definition(parameter& parameter)
{
	if (!any_of(parameter, ":").second) {
		return error::code::expected_declaration_statement;
	}
	parameter.bundle.add(token{ token::keyword::type_definition });
	eat_whitespaces(parameter);
	if (const auto err = identifier(parameter)) {
		return err;
	}
	return {};
}
