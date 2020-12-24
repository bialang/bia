#include "../type/integer.hpp"
#include "helpers.hpp"

using namespace bia::compiler;

std::pair<elve::tokens_type, bia::util::not_null<type::definition*>>
  elve::single_expression(parameter& param, tokens_type tokens, destination_type destination, bool atomic)
{
	// BIA_EXPECTS(tokens.front());
	BIA_EXPECTS(tokens.front().value.is_type<tokenizer::token::token::number>());
	const auto def = param.symbols.get_symbol(util::from_cstring("int"));
	BIA_EXPECTS(def.is_type<type::definition*>());
	const auto number = tokens.front().value.get<tokenizer::token::token::number>();
	param.writer.write<bytecode::Op_code::oc_push>(number.value.i);
	return { tokens.subspan(1), def.get<type::definition*>() };
}
