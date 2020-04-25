#ifndef BIA_TOKENIZER_TOKEN_PARSE_WHILE_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_WHILE_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"
#include "expression.hpp"
#include "whitespace_eater.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

exception::syntax_details single_stmt(parameter& parameter);
exception::syntax_details cmd_end(parameter& parameter);

inline exception::syntax_details while_(parameter& parameter)
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

	if (parameter.encoder.read(parameter.input) != '{') {
		return { parameter.input.tellg(), "expected '{'" };
	}

	const auto open_index = parameter.bundle.add({ token::batch{ 0 } });
	std::size_t count     = 0;

	while (true) {
		const auto old = parameter.backup();

		eat_whitespaces(parameter);

		if (single_stmt(parameter)) {
			parameter.restore(old);

			break;
		}

		if (const auto err = cmd_end(parameter)) {
			return err;
		}

		++count;
	}

	eat_whitespaces(parameter);

	if (parameter.encoder.read(parameter.input) != '}') {
		return { parameter.input.tellg(), "expected '}'" };
	}

	parameter.bundle.at(open_index).value.get<token::batch>().count = count;

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif