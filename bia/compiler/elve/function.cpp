#include "../jump_manager.hpp"
#include "helpers.hpp"

#include <bia/log/log.hpp>
#include <sstream>

bia::compiler::elve::tokens_type bia::compiler::elve::function(present present, tokens_type tokens)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() && is_keyword(tokens.data(), token::keyword::fun));

	// create destination variable
	bytecode::member::local destination;

	{
		auto index = present.variables.find(tokens.data()[1].value.get<token::identifier>().memory);

		if (!index.second) {
			index.first = present.variables.add(tokens.data()[1].value.get<token::identifier>().memory);
		}

		destination = { index.first };
	}

	auto variables = present.variables.open_scope();
	std::stringstream code;
	bytecode::writer::instruction writer{ code };

	tokens = batch({ variables, writer, present.resources, present.manager }, tokens.subspan(2));

	writer.finish();

	// todo:
	auto streambuf = present.manager.start_memory(false);
	code.seekg(0, std::ios_base::beg);
	std::ostream{ &streambuf } << code.rdbuf();

	// initiate function
	present.writer.write<true, bytecode::oc_initiate>(
	    bytecode::member::resource{ present.resources.index_of(streambuf.finish(resource::type::function)) },
	    destination);

	// bind references
	for (const auto& i : variables.bindings()) {
		BIA_LOG(DEBUG, "binding variable from {} to {}", i.first, i.second);

		present.resources.add_binding(i.first, i.second);
	}

	return tokens;
}
