#include "any_of.hpp"
#include "batch.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

inline std::error_code else_if(bia::tokenizer::token::parameter& parameter)
{
	using namespace bia::tokenizer::token;
	using namespace parse;

	// compare else
	if (!any_of(parameter, "invalid else if statement", "else").second) {
		return bia::error::code::bad_else_if_statement;
	} else if (const auto err = eat_whitespaces(parameter)) {
		return err;
	} else if (!any_of(parameter, "invalid else if statement", "if").second) {
		return bia::error::code::bad_else_if_statement;
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

std::error_code bia::tokenizer::token::parse::else_(parameter& parameter)
{
	// compare else
	if (!any_of(parameter, "else").second) {
		return error::code::bad_else_statement;
	}

	parameter.bundle.add({ token::keyword::else_ });

	eat_whitespaces(parameter);

	return batch(parameter, no_batch_call);
}

std::error_code bia::tokenizer::token::parse::if_(parameter& parameter)
{
	// compare if
	if (!any_of(parameter, "if").second) {
		return error::code::bad_if_statement;
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
