#include "any_of.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

#include <bia/exception/implementation_error.hpp>

bia::exception::syntax_details bia::tokenizer::token::parse::value(parameter& parameter)
{
	// constant
	const auto old = parameter.backup();
	const auto t   = any_of(parameter, nullptr, "true", "false", "null");

	if (!t.second) {
		switch (t.first) {
		case 0: parameter.bundle.add(token{ token::keyword::true_ }); break;
		case 1: parameter.bundle.add(token{ token::keyword::false_ }); break;
		case 2: parameter.bundle.add(token{ token::keyword::null }); break;
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

	// regex
	if (!regex(parameter)) {
		return {};
	}

	parameter.restore(old);

	// member
	if ((err = member(parameter))) {
		return err;
	}

	return {};
}

bia::exception::syntax_details bia::tokenizer::token::parse::term(parameter& parameter)
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

bia::exception::syntax_details bia::tokenizer::token::parse::expression(parameter& parameter)
{
	if (const auto err = term(parameter)) {
		return err;
	}

	// more
	while (true) {
		const auto old = parameter.backup();

		eat_whitespaces(parameter);

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

			if (op == operator_::member_access) {
				if (const auto err = member(parameter)) {
					return err;
				}
			} else if (const auto err = term(parameter)) {
				return err;
			}
		}
	}

	return {};
}
