#include "any_of.hpp"
#include "batch.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

std::error_code bia::tokenizer::token::parse::function(parameter& parameter)
{
	if (!any_of(parameter, "fun").second) {
		return error::code::bad_function_statement;
	}

	parameter.bundle.add({ token::keyword::fun });

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (const auto err = identifier(parameter)) {
		return err;
	}

	eat_whitespaces(parameter);

	if (const auto err = batch(parameter, no_batch_call)) {
		return err;
	}

	return {};
}
