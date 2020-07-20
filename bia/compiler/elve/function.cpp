#include "../jump_manager.hpp"
#include "helpers.hpp"

#include <sstream>

bia::compiler::elve::tokens_type bia::compiler::elve::function(present present, tokens_type tokens)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() && is_keyword(tokens.data(), token::keyword::fun));

	// auto variables = present.variables.open_scope();
	auto binder    = present.resources;
	auto streambuf = present.manager.start_memory(false);
	std::ostream code{ &streambuf };
	bytecode::writer::instruction writer{ code };

	tokens = batch({ present.variables, writer, binder, present.manager }, tokens.subspan(2));

	writer.write<true, bytecode::oc_return_void>();

	// bind references
	/*variables.bind();
	binder.bind();*/

	// create destination variable
	auto index = present.variables.find(tokens.data()[1].value.get<token::identifier>().memory);

	if (!index.second) {
		index.first = present.variables.add(tokens.data()[1].value.get<token::identifier>().memory);
	}

	// initiate function
	present.writer.write<true, bytecode::oc_initiate>(
	    bytecode::member::resource{ present.resources.index_of(streambuf.finish(resource::type::function)) },
	    bytecode::member::local{ index.first });

	return tokens;
}
