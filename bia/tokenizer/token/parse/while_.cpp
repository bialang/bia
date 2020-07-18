#include "any_of.hpp"
#include "batch.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

bia::exception::syntax_details bia::tokenizer::token::parse::while_(parameter& parameter)
{
	// compare while
	if (const auto err = any_of(parameter, "invalid while statement", "while").second) {
		return err;
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
