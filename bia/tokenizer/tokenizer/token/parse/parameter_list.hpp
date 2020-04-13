#ifndef BIA_TOKENIZER_TOKEN_PARSE_PARAMETER_LIST_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_PARAMETER_LIST_HPP_

#include "../parameter.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

exception::syntax_details expression(parameter& parameter);

inline exception::syntax_details parameter_list(parameter& parameter)
{
	auto pos = parameter.input.tellg();

	if (parameter.encoder.read(parameter.input) != '(') {
		return { pos, "expected '('" };
	}

	// parse first parameter
	auto last       = parameter.bundle.add({ token::control{ token::control::type::bracket_open, 0 } });
	const auto base = last;
	const auto old  = parameter.backup();
	const auto update_last = [&last, &parameter, base](enum token::control::type type) {
		const auto index = parameter.bundle.add({ token::control{ type, last - base } });

		last = index;
	};

	if (const auto err = expression(parameter)) {
		parameter.restore(old);

		pos = parameter.input.tellg();

		// must close when no parameter
		if (parameter.encoder.read(parameter.input) != ')') {
			return { pos, "expected ')'" };
		}

		goto gt_success;
	}

	while (true) {
		switch (parameter.encoder.read(parameter.input)) {
		case ')': goto gt_success;
		case ',': {
			update_last(token::control::type::comma);

			if (const auto err = expression(parameter)) {
				return err;
			}

			break;
		}
		}
	}

gt_success:;
	update_last(token::control::type::bracket_close);

	// open bracket points to close bracket
	parameter.bundle.at(base).value.get<token::control>().value = last - base;

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif