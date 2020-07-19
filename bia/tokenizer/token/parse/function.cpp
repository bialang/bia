#include "any_of.hpp"
#include "batch.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

bia::exception::syntax_details bia::tokenizer::token::parse::function(parameter& parameter)
{
	if (const auto err = any_of(parameter, "invalid function statement", "fun").second) {
		return err;
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
