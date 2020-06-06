#ifndef BIA_TOKENIZER_TOKEN_PARSE_EXPRESSION_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_EXPRESSION_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"
#include "identifier.hpp"
#include "member.hpp"
#include "number.hpp"
#include "operators.hpp"
#include "string.hpp"
#include "whitespace_eater.hpp"

#include <bia/exception/implementation_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details value(parameter& parameter)
{
	// constant
	const auto old = parameter.backup();
	const auto t   = any_of(parameter, nullptr, "true", "false");

	if (!t.second) {
		switch (t.first) {
		case 0: parameter.bundle.add(token{ token::keyword::true_ }); break;
		case 1: parameter.bundle.add(token{ token::keyword::false_ }); break;
		default: BIA_IMPLEMENTATION_ERROR("invalid keyword id");
		}

		return {};
	}

	parameter.restore(old);

	// number
	auto err = number(parameter);

	if (!err) {
		return {};
	}

	parameter.restore(old);

	// string
	if (!string(parameter)) {
		return {};
	}

	parameter.restore(old);

	// member
	if ((err = member(parameter))) {
		return err;
	}

	return {};
}

inline exception::syntax_details term(parameter& parameter)
{
	// match optional self operator
	const auto old = parameter.backup();
	const auto t   = any_of(parameter, nullptr, "not", "~", "-");

	// match self operator, but whitespace required if operator is 'not'
	if (!t.second && !(eat_whitespaces(parameter) && t.first == 0)) {
		switch (t.first) {
		case 0: parameter.bundle.add({ operator_::logical_not }); break;
		case 1: parameter.bundle.add({ operator_::bitwise_not }); break;
		case 2: parameter.bundle.add({ operator_::unary_minus }); break;
		default: BIA_IMPLEMENTATION_ERROR("invalid operator id");
		}
	} else {
		parameter.restore(old);
	}

	// match value
	return value(parameter);
}

inline exception::syntax_details expression(parameter& parameter)
{
	if (const auto err = term(parameter)) {
		return err;
	}

	// more
	while (true) {
		const auto old = parameter.backup();

		if (const auto err = eat_whitespaces(parameter)) {
			break;
		}

		if (const auto err = operators(parameter)) {
			parameter.restore(old);

			break;
		}

		// only if operator is infix
		const auto op = parameter.bundle.last().value.get<operator_>();

		if (type_of(op) == operator_type::infix) {
			if (const auto err = eat_whitespaces(parameter)) {
				// whitespaces are required
				if (op == operator_::in || op == operator_::logical_and || op == operator_::logical_or) {
					return err;
				}
			}

			if (const auto err = term(parameter)) {
				return err;
			}
		}
	}

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
