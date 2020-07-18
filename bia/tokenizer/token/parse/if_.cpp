#include "any_of.hpp"
#include "batch.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

inline bia::exception::syntax_details else_if(bia::tokenizer::token::parameter& parameter)
{
	using namespace bia::tokenizer::token;
	using namespace parse;

	// compare else
	if (const auto err = any_of(parameter, "invalid else if statement", "else").second) {
		return err;
	} else if (const auto err = eat_whitespaces(parameter)) {
		return err;
	} else if (const auto err = any_of(parameter, "invalid else if statement", "if").second) {
		return err;
	}

	parameter.bundle.add({ token::keyword::else_if });

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (const auto err = expression(parameter)) {
		return err;
	}

	eat_whitespaces(parameter);

	return batch(parameter, no_batch_call);
}

bia::exception::syntax_details bia::tokenizer::token::parse::else_(parameter& parameter)
{
	// compare else
	if (const auto err = any_of(parameter, "invalid else statement", "else").second) {
		return err;
	}

	parameter.bundle.add({ token::keyword::else_ });

	eat_whitespaces(parameter);

	return batch(parameter, no_batch_call);
}

bia::exception::syntax_details bia::tokenizer::token::parse::if_(parameter& parameter)
{
	// compare if
	if (const auto err = any_of(parameter, "invalid if statement", "if").second) {
		return err;
	}

	parameter.bundle.add({ token::keyword::if_ });

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (const auto err = expression(parameter)) {
		return err;
	}

	eat_whitespaces(parameter);

	if (const auto err = batch(parameter, no_batch_call)) {
		return err;
	}

	while (true) {
		const auto old = parameter.backup();

		eat_whitespaces(parameter);

		if (const auto err = else_if(parameter)) {
			parameter.restore(old);

			break;
		}
	}

	const auto old = parameter.backup();

	eat_whitespaces(parameter);

	if (else_(parameter)) {
		parameter.restore(old);
	}

	return {};
}
