#include "../type/integer.hpp"
#include "helpers.hpp"

using namespace bia::compiler;

std::pair<elve::tokens_type, bia::util::not_null<type::definition*>>
  elve::single_expression(parameter& param, tokens_type tokens, destination_type destination, bool atomic)
{
	// BIA_EXPECTS(tokens.front());
	BIA_EXPECTS(tokens.front().value.is_type<tokenizer::token::token::number>());
	static type::integer def{ type::integer::size::i };

	const auto number = tokens.front().value.get<tokenizer::token::token::number>();
	param.writer.write<false, bytecode::oc_instantiate>(number.value.i,
	                                                    destination.get<bytecode::member::local>());
	return { tokens.subspan(1), &def };
}
