#include "../jumper.hpp"
#include "helpers.hpp"

#include <bia/internal/type/integral.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;
using namespace bia::internal;

elve::Tokens elve::while_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Keyword::while_);

	Jumper jumper{ param.instructor };
	jumper.mark(Jumper::Destination::start);
	param.flow_controller.start_flow(jumper);

	// condition
	util::Optional<symbol::Local_variable> variable;
	auto expression_tokens     = tokens.subspan(1);
	std::tie(tokens, variable) = single_expression(param, expression_tokens);

	if (!dynamic_cast<const type::Definition<bool>*>(variable->definition)) {
		param.errors.add_error(error::Code::not_boolean, expression_tokens.left(tokens.begin()));
	}

	param.symbols.free_temporary(*variable);
	jumper.jump(Jumper::Type::if_false, Jumper::Destination::end);

	// statements
	tokens = batch(param, tokens);
	jumper.jump(Jumper::Type::unconditional, Jumper::Destination::start);
	jumper.mark(Jumper::Destination::end);
	param.flow_controller.end_flow();
	return tokens;
}
