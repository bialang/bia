#include "any_of.hpp"
#include "tokens.hpp"

bia::exception::syntax_details bia::tokenizer::token::parse::loop_flow_control(parameter& parameter)
{
	const auto x = any_of(parameter, "expected 'break' or 'continue'", "break", "continue");

	if (x.second) {
		return x.second;
	}

	parameter.bundle.add({ static_cast<token::keyword>(x.first + static_cast<int>(token::keyword::break_)) });

	return {};
}
