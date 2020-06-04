#ifndef BIA_COMPILER_ELVE_IMPORT_HPP_
#define BIA_COMPILER_ELVE_IMPORT_HPP_

#include "expression.hpp"
#include "present.hpp"

namespace bia {
namespace compiler {
namespace elve {

inline tokens_type import(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(tokens.size() >= 2 &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword);

	const auto variable =
	    present.variable_manager.index_of(tokens.data()[1].value.get<token::identifier>().memory);
	const bytecode::member::resource name{ present.resources.index_of(
		tokens.data()[1].value.get<token::identifier>().memory) };

	// overwrite existing variable
	if (variable.second) {
		// overwriting of other scopes not implemented
		BIA_EXPECTS(variable.first.scope_id == 0);

		present.writer.write<true, bytecode::oc_import>(name, bytecode::member::local{ variable.first.id });
	} else {
		present.variable_manager.add(tokens.data()[1].value.get<token::identifier>().memory);

		present.writer.write<true, bytecode::oc_import>(name, bytecode::member::tos{});
	}

	return tokens.subspan(2);
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
