#include "any_of.hpp"
#include "tokens.hpp"

std::error_code bia::tokenizer::token::parse::loop_flow_control(parameter& parameter)
{
	const auto x = any_of(parameter, "break", "continue");

	if (x.second) {
		return error::code::expected_flow_control;
	}

	parameter.bundle.add({ static_cast<token::keyword>(x.first + static_cast<int>(token::keyword::break_)) });

	return {};
}
