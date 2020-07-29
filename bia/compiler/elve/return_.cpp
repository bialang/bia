#include "../jump_manager.hpp"
#include "helpers.hpp"

#include <sstream>

bia::compiler::elve::tokens_type bia::compiler::elve::return_(present present, tokens_type tokens)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() && is_keyword(tokens.data(), token::keyword::return_));

	bytecode::member::local tmp{ present.variables.add_tmp() };

	tokens = expression(present, tokens.subspan(1), tmp);

	present.writer.write<true, bytecode::oc_return>(tmp);
	present.variables.remove_tmp(tmp.index);

	return tokens;
}
