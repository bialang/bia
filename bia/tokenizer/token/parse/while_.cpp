#include "any_of.hpp"
#include "batch.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

std::error_code bia::tokenizer::token::parse::while_(parameter& parameter)
{
	// compare while
	if (!any_of(parameter, "while").second) {
		return error::code::expected_while_statement;
	}

	parameter.bundle.add({ token::keyword::while_ });

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (const auto err = expression(parameter)) {
		return err;
	}

	eat_whitespaces(parameter);

	return batch(parameter, [&parameter] { return loop_flow_control(parameter); });
}
