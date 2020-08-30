#include "expression.hpp"
#include "helpers.hpp"

#include <bia/error/exception.hpp>

bia::compiler::elve::tokens_type bia::compiler::elve::declaration(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(tokens.size() > 2 &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword);

	const auto variable = present.variables.find(tokens.data()[1].value.get<token::identifier>().memory);

	// overwrite existing variable
	if (variable.second) {
		switch (variable.first.second) {
		case manager::variable::type::local:
			return expression(present, tokens.subspan(2), bytecode::member::local{ variable.first.first });
		case manager::variable::type::argument:
			return expression(present, tokens.subspan(2), bytecode::member::args{ variable.first.first });
		default: BIA_THROW(error::code::bad_switch_value);
		}
	}

	return expression(
	    present, tokens.subspan(2),
	    bytecode::member::local{ present.variables.add(tokens.data()[1].value.get<token::identifier>().memory,
	                                                   manager::variable::type::local) });
}
