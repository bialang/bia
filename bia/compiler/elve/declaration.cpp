#include "expression.hpp"
#include "helpers.hpp"

bia::compiler::elve::tokens_type bia::compiler::elve::declaration(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(tokens.size() > 2 &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword);

	const auto index = present.variables.find(tokens.data()[1].value.get<token::identifier>().memory);

	// overwrite existing variable
	if (index.second) {
		return expression(present, tokens.subspan(2), bytecode::member::local{ index.first });
	}

	return expression(present, tokens.subspan(2),
	                  bytecode::member::local{
	                      present.variables.add(tokens.data()[1].value.get<token::identifier>().memory) });
}
