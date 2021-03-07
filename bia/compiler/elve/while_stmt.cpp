#include "../jumper.hpp"
#include "helpers.hpp"

using namespace bia::compiler;
using namespace bia::tokenizer::token;
using namespace bia::internal;

elve::Tokens elve::while_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Keyword::while_);

	Jumper jumper{ param.instructor };
	jumper.mark(Jumper::Destination::start);

	// condition
	util::Optional<symbol::Variable> variable;
	auto expression_tokens     = tokens.subspan(1);
	std::tie(tokens, variable) = single_expression(param, expression_tokens);
	expression_tokens          = expression_tokens.left(tokens.begin());

	// TODO size of op code
	switch (variable->definition->size()) {
	case 1: param.instructor.write<bytecode::Op_code::truthy, std::int8_t>(variable->location.offset); break;
	case 2: param.instructor.write<bytecode::Op_code::truthy, std::int16_t>(variable->location.offset); break;
	case 4: param.instructor.write<bytecode::Op_code::truthy, std::int32_t>(variable->location.offset); break;
	case 8: param.instructor.write<bytecode::Op_code::truthy, std::int64_t>(variable->location.offset); break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}

	param.symbols.free_temporary(*variable);
	jumper.jump(Jumper::Type::if_false, Jumper::Destination::end);

	// statements
	tokens = batch(param, tokens);
	jumper.jump(Jumper::Type::unconditional, Jumper::Destination::start);
	jumper.mark(Jumper::Destination::end);
	return tokens;
}
