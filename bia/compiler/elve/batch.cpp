#include "helpers.hpp"

bia::compiler::elve::tokens_type bia::compiler::elve::batch(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::batch);

	auto count = tokens.data()->value.get<token::batch>().count;

	tokens = tokens.subspan(1);

	while (count--) {
		tokens = statement(present, tokens);
	}

	return tokens;
}
