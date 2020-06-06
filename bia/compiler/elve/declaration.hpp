#ifndef BIA_COMPILER_ELVE_DECLARATION_HPP_
#define BIA_COMPILER_ELVE_DECLARATION_HPP_

#include "expression.hpp"
#include "present.hpp"

namespace bia {
namespace compiler {
namespace elve {

inline tokens_type declaration(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(tokens.size() > 2 &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword);

	const auto index =
	    present.variable_manager.index_of(tokens.data()[1].value.get<token::identifier>().memory);

	// overwrite existing variable
	if (index.second) {
		// overwriting of other scopes not implemented
		BIA_EXPECTS(index.first.scope_id == 0);

		return expression(present, tokens.subspan(2), bytecode::member::local{ index.first.id });
	}

	const auto ret = expression(present, tokens.subspan(2), bytecode::member::tos{});

	present.variable_manager.add(tokens.data()[1].value.get<token::identifier>().memory);

	return ret;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
