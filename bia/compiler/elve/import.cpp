#include "helpers.hpp"

bia::compiler::elve::tokens_type bia::compiler::elve::import(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(tokens.size() >= 2 &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword);

	const auto variable = present.variables.find(tokens.data()[1].value.get<token::identifier>().memory);
	const bytecode::member::resource name{ present.resources.index_of(
		tokens.data()[1].value.get<token::identifier>().memory) };

	// overwrite existing variable
	if (variable.second) {
		present.writer.write<true, bytecode::oc_import>(name, bytecode::member::local{ variable.first });
	} else {
		present.writer.write<true, bytecode::oc_import>(
		    name, bytecode::member::local{
		              present.variables.add(tokens.data()[1].value.get<token::identifier>().memory) });
	}

	return tokens.subspan(2);
}
