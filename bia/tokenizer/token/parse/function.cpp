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

	if (parameter.encoder.read(parameter.input) != '(') {
		return error::code::expected_parameter_list;
	}

	parameter.bundle.add({ token::control{ token::control::type::bracket_open, 0 } });

	for (auto first = true; true; first = false) {
		eat_whitespaces(parameter);
		const auto old = parameter.backup();

		if (first || parameter.encoder.read(parameter.input) == ',') {
			eat_whitespaces(parameter);

			if (!identifier(parameter)) {
				continue;
			}
		}

		parameter.restore(old);

		if (parameter.encoder.read(parameter.input) != ')') {
			return error::code::expected_parameter_list;
		}

		parameter.bundle.add({ token::control{ token::control::type::bracket_close, 0 } });
		eat_whitespaces(parameter);
		break;
	}

	if (const auto err = batch(parameter, no_batch_call)) {
		return err;
	}

	return {};
}
