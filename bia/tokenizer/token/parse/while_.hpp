#ifndef BIA_TOKENIZER_TOKEN_PARSE_WHILE_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_WHILE_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"
#include "batch.hpp"
#include "expression.hpp"
#include "flow_control.hpp"
#include "whitespace_eater.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

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

	return batch(parameter, [&parameter] { return loop_flow_control(parameter); });
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
