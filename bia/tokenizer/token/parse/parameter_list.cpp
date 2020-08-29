#include "tokens.hpp"
#include "whitespace_eater.hpp"

inline std::error_code parameter_element(bia::tokenizer::token::parameter& parameter)
{
	using namespace bia::tokenizer::token;
	using namespace parse;

	const auto old = parameter.backup();

	parameter.bundle.add({ token::control{ token::control::type::key, 1 } });

	if (!identifier(parameter)) {
		eat_whitespaces(parameter);

		if (parameter.encoder.read(parameter.input) == '=') {
			eat_whitespaces(parameter);

			return expression(parameter);
		}
	}

	parameter.restore(old);

	return expression(parameter);
}

std::error_code bia::tokenizer::token::parse::parameter_list(parameter& parameter)
{
	auto pos = parameter.input.tellg();

	if (parameter.encoder.read(parameter.input) != '(') {
		return error::code::expected_parameter_list;
	}

	eat_whitespaces(parameter);

	// parse first parameter
	auto last      = parameter.bundle.add({ token::control{ token::control::type::bracket_open, 0 } });
	const auto old = parameter.backup();
	const auto update_last = [&last, &parameter](enum token::control::type type) {
		const auto index = parameter.bundle.add({ token::control{ type, 0 } });

		parameter.bundle.at(last).value.get<token::control>().value = index - last;

		last = index;
	};

	if (const auto err = parameter_element(parameter)) {
		parameter.restore(old);

		pos = parameter.input.tellg();

		// must close when no parameter
		if (parameter.encoder.read(parameter.input) != ')') {
			return error::code::expected_parameter_list;
		}

		goto gt_success;
	}

	while (true) {
		eat_whitespaces(parameter);

		pos = parameter.input.tellg();

		switch (parameter.encoder.read(parameter.input)) {
		case ')': goto gt_success;
		case ',': {
			update_last(token::control::type::comma);
			eat_whitespaces(parameter);

			if (const auto err = parameter_element(parameter)) {
				return err;
			}

			break;
		}
		default: return error::code::expected_parameter_list;
		}
	}

gt_success:;
	update_last(token::control::type::bracket_close);

	return {};
}
