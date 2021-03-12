#include "helpers.hpp"

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::flow_control_stmt(Parameter& param, Tokens tokens)
{
	if (tokens.front().value == Token::Keyword::break_) {
		param.flow_controller.break_flow();
	} else {
		param.flow_controller.continue_flow();
	}
	return tokens.subspan(1);
}
