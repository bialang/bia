#ifndef BIA_TOKENIZER_TOKEN_PARSE_EXPRESSION_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_EXPRESSION_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"
#include "identifier.hpp"
#include "member.hpp"
#include "operators.hpp"

#include <exception/implementation_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details value(parameter& parameter)
{
	// constant
	const auto old = parameter.backup();
	auto t         = any_of(parameter, nullptr, "true", "false", "null");

	if (t.first) {
		switch (t.first) {
		case 1: parameter.bundle.add(token{ token::keyword::true_ }); break;
		case 2: parameter.bundle.add(token{ token::keyword::false_ }); break;
		case 3: parameter.bundle.add(token{ token::keyword::null }); break;
		default: BIA_IMPLEMENTATION_ERROR("invalid keyword id");
		}

		return {};
	}

	parameter.restore(old);

	// member
	if (auto err = member(parameter)) {
		return err;
	}

	return {};
}

inline exception::syntax_details term(parameter& parameter)
{
	// match optional self operator
	auto t = any_of(parameter, nullptr, "not", "~", "-");

	if (t.first) {
		switch (t.first) {
		case 1: parameter.bundle.add(token{ token::keyword::not_ }); break;
		case 2: parameter.bundle.add(token{ token::operator_::tilde }); break;
		case 3: parameter.bundle.add(token{ token::operator_::minus }); break;
		default: BIA_IMPLEMENTATION_ERROR("invalid operator id");
		}
	}

	// match value
	return value(parameter);
}

inline exception::syntax_details expression(parameter& parameter)
{
	if (auto err = term(parameter)) {
		return err;
	}

	// end of expression
	if (auto err = operators(parameter)) {
		return {};
	}

	if (auto err = term(parameter)) {
		return {};
	}

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif