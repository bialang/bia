#ifndef BIA_TOKENIZER_TOKEN_PARSE_FOR_EACH_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_FOR_EACH_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"
#include "batch.hpp"
#include "expression.hpp"
#include "whitespace_eater.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details for_each(parameter& parameter)
{
	// compare if
	if (const auto err = any_of(parameter, "invalid for statement", "for").second) {
		return err;
	}

	parameter.bundle.add({ token::keyword::for_ });

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (const auto err = identifier(parameter)) {
		return err;
	}

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (const auto err = any_of(parameter, "invalid in statement", "in").second) {
		return err;
	}

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

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
