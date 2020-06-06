#ifndef BIA_TOKENIZER_TOKEN_PARSE_FLOW_CONTROL_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_FLOW_CONTROL_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details loop_flow_control(parameter& parameter)
{
	const auto x = any_of(parameter, "expected 'break' or 'continue'", "break", "continue");

	if (x.second) {
		return x.second;
	}

	parameter.bundle.add({ static_cast<token::keyword>(x.first + static_cast<int>(token::keyword::break_)) });

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif